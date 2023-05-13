/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdmgr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:39:20 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/13 17:28:04 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdmgr.h"

void	free_args(char **cmd_args)
{
	char	**head;
	
	head = cmd_args;
	while (*head)
	{
		free(*head);
		head++;
	}
	free(cmd_args);
}

// Now. How to use execve instead of execvp? What's the problem.
int	exec_cmd(char *cmd, int fd)
{
	int		pid;
	int		wstatus;
	char	**cmd_args;

	pid = fork();
	cmd_args = NULL;
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		cmd_args = ft_split(cmd, '\x20');
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			free_args(cmd_args);
			perror(NULL);
			exit(EXIT_FAILURE);
		}
		execvp(cmd_args[0], cmd_args);
	}
	else
	{
		if (wait(&wstatus) == -1 || (wstatus >> 8 & 0xFF) == EXIT_FAILURE)
			return (-1);
	}
	return (0);
}
