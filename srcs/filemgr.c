/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filemgr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 22:58:16 by jgermany          #+#    #+#             */
/*   Updated: 2025/05/04 17:08:55 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	fmgr_open(char *path, int openflags, mode_t openmode)
{
	int	fd;

	fd = open(path, openflags, openmode);
	if (fd == -1 && ft_eprintf(ERR_PATH, path, strerror(errno)))
		return (-1);
	return (fd);
}

int	fmgr_pipe(int fds[2])
{
	if (pipe(fds) == -1 && ft_eprintf(ERR_GENERIC, strerror(errno)))
		return (-1);
	return (0);
}

int	fmgr_close(int from, int reverse, t_prg *prgs)
{
	t_prg	prg;
	
	while ((reverse && from >= 0) || (!reverse && prgs[from].cmd))
	{
		prg = prgs[from];
		if ((from == 0 && prg.in[0] > -1 && close(prg.in[0]) == -1)
			|| (prg.out[0] > -1 && close(prg.out[0]) == -1)
			|| (prg.out[1] > -1 && close(prg.out[1]) == -1))
		{
			ft_eprintf(ERR_GENERIC, strerror(errno));
			return (-1);
		}
		if (reverse)
			from--;
		else
			++from;
	}
	return (0);
}

// 25/04 - Why are these things below part of filemgr?
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
