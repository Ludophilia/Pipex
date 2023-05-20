/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdmgr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:39:20 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/20 18:52:55 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdmgr.h"

void	exec_cmd(char *cmd, int fd, char **envp)
{
	char	**cmd_args;

	cmd_args = ft_split(cmd, '\x20');
	if (ft_strchr(cmd_args[0], '/') == NULL)
	{
		cmd_args[0] = search_executable(cmd_args[0], envp);
		if (cmd_args[0] == NULL)
		{
			errno = ENOENT;
			dprintf(2, "pipex: command not found: '%s'\n", cmd);
			free_strs(cmd_args, 1);
			exit(EXIT_FAILURE);
		}
	}
	else if (check_perm(cmd_args[0], X_OK) == -1)
	{
		free_strs(cmd_args, 0);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, 0) == -1 || execve(cmd_args[0], cmd_args, envp) == -1)
	{
		perror("pipex");
		free_strs(cmd_args, 0);
		exit(EXIT_FAILURE);
	}
}

// move R_OK, O_RDONLY in the args in a struct or something
int	redir_and_exec(char *file, char *cmd, char **envp)
{
	int		fd;
	int		pid;
	int		wstatus;

	fd = check_and_open(file, R_OK, O_RDONLY);
	if (fd == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		perror(NULL);
		return (-1);
	}
	else if (pid == 0)
		exec_cmd(cmd, fd, envp);
	else
	{
		if (wait(&wstatus) == -1 || (wstatus >> 8 & 0xFF) == EXIT_FAILURE)
		{
			perror(NULL);
			return (-1);
		}
	}
	close(fd);
	return (0);
}
