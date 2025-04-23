/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filemgr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 22:58:16 by jgermany          #+#    #+#             */
/*   Updated: 2025/04/23 21:15:27 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	check_and_close_fds(t_cmd *cmdenvs, int head)
{
	if (cmdenvs[head].in[0] > -1)
		close(cmdenvs[head].in[0]);
	if (cmdenvs[head].out[1] > -1)
		close(cmdenvs[head].out[1]);
	if (cmdenvs[head].in[1] > -1)
		close(cmdenvs[head].in[1]);
	if (cmdenvs[head].out[0] > -1)
		close(cmdenvs[head].out[0]);
}

void	close_fds(t_cmd *cmdenvs, int head, int reverse)
{
	if (reverse)
	{
		while (head >= 0)
		{
			check_and_close_fds(cmdenvs, head);
			head--;
		}
		return ;
	}
	head -= 1;
	while (cmdenvs[++head].cmd)
		check_and_close_fds(cmdenvs, head);
}

int	check_and_open(char *path, int openflags, mode_t openmode)
{
	int	fd;

	fd = open(path, openflags, openmode);
	if (fd == -1)
	{
		ft_eprintf("pipex: %s: %s\n", path, strerror(errno));
		return (-1);
	}
	return (fd);
}

static char	**get_paths(char **envp)
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
