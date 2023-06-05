/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filemgr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 22:58:16 by jgermany          #+#    #+#             */
/*   Updated: 2023/06/05 17:24:25 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filemgr.h"

static void	check_and_close_fds(t_cmd *cmdenvs, int head)
{
	if (cmdenvs[head].in[0] != -1)
		close(cmdenvs[head].in[0]);
	if (cmdenvs[head].out[1] != -1)
		close(cmdenvs[head].out[1]);
	if (cmdenvs[head].in[1] != -1)
		close(cmdenvs[head].in[1]);
	if (cmdenvs[head].out[0] != -1)
		close(cmdenvs[head].out[0]);
}

void	close_fds(t_cmd *cmdenvs, int head, int reverse)
{
	if (reverse)
	{
		while (head-- >= 0)
			check_and_close_fds(cmdenvs, head);
		return ;
	}
	head -= 1;
	while (cmdenvs[++head].cmd)
		check_and_close_fds(cmdenvs, head);
}

int	check_and_open(char *path, int accessmode, int openflags, mode_t openmode)
{
	int bypass_check;
	int	fd;

	bypass_check = 0;
	if (accessmode == W_OK && access(path, F_OK) == -1)
		bypass_check = 1;
	if (bypass_check == 0 && check_perm(path, accessmode) == -1)
		return (-1);
	fd = open(path, openflags, openmode);
	if (fd == -1)
		return (-1);
	return (fd);
}

char	**get_paths(char **envp)
{
	while (*envp)
	{
		if (ft_strnstr(*envp, "PATH", 4))
			return (ft_split(*envp + 5, ':'));
		envp++;
	}
	return (ft_split(DEFAULT_PATH, ':'));
}

char	*search_executable(char *cmd, char **envp)
{
	char	**paths;
	char	*candidate;
	char	*suffix;
	int		i;

	paths = get_paths(envp);
	i = -1;
	while (paths[++i])
	{
		suffix = ft_strjoin("/", cmd);
		candidate = ft_strjoin(paths[i], suffix);
		free(suffix);
		if (access(candidate, X_OK) == 0)
		{
			free_strs(paths, 0);
			return (candidate);
		}
		free(candidate);
	}
	free_strs(paths, 0);
	free(cmd);
	return (NULL);
}
