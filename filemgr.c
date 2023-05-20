/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filemgr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 22:58:16 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/20 18:55:14 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filemgr.h"

int	check_and_open(char *path, int accessmode, int openmode)
{
	int	fd;

	if (check_perm(path, accessmode) == -1)
		return (-1);
	fd = open(path, openmode);
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
