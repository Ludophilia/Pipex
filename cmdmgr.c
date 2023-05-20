/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdmgr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:39:20 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/20 14:12:40 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdmgr.h"

char 	**get_paths(char **envp)
{
	while (*envp)
	{
		if (ft_strnstr(*envp, "PATH", 4))
			return (ft_split(*envp + 5, ':'));
		envp++;
	}
	return (ft_split(DEFAULT_PATH, ':'));
}


char	*search_executable(char *cmd, char **envp) // ex: `tee` or `ls`
{
	char	**paths;
	char	*candidate;
	int		i;

	paths = get_paths(envp);
	i = -1;
	while (paths[++i])
	{
		candidate = ft_strjoin(paths[i], cmd);
		if (check_perm(candidate, X_OK) == 0)
			return (candidate);
		free(candidate);
	}
	free_strs(paths);
	return (NULL); // And what if the search_executable() return NULL?
}

void	exec_cmd(char *cmd, int fd, char **envp)
{
	char	**cmd_args;

	cmd_args = ft_split(cmd, '\x20'); // ex -> ["ls", "-hltc"]
	if (!ft_strchr(cmd_args[0], '/'))
	{
		cmd_args[0] = search_executable(cmd_args[0], envp);
		// And what if search_executable() return NULL ?
	}
	// Once the path to the executable is cleared (if needed), it's important 
	// to test what if cmd_args[0] does not exist or is not executable?
	if (check_perm(cmd_args[0], X_OK) == -1 || dup2(fd, STDIN_FILENO) == -1
		|| execve(cmd_args[0], cmd_args, envp) == -1)
	{
		free_strs(cmd_args);
		perror("pipex");
		exit(EXIT_FAILURE);
	}
}

int		redir_and_exec(char *file, char *cmd, char **envp)
{
	int		fd;
	int		pid;
	int		wstatus;

	fd = check_and_open(file, R_OK, O_RDONLY); // move R_OK, O_RDONLY in the args in a struct or something
	if (fd == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		perror(NULL);
		return (-1);
	}
	else if (pid == 0)
	{
		exec_cmd(cmd, fd, envp);
	}
	else
	{
		if (wait(&wstatus) == -1 || (wstatus >> 8 & 0xFF) == EXIT_FAILURE)
		{
			// perror(NULL);
			// dprintf(2, "pipex: An error")
			return (-1);
		}
	}
	close(fd);
	return (0);
}
