/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdmgr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:39:20 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/13 12:04:32 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdmgr.h"

int	exec_cmd(char *cmd, int fd)
{
	int		pid;
	int		wstatus;
	char	**cmd_args;

	cmd_args = ft_split(cmd, '\x20'); // LEAK?
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if (dup2(fd, STDIN_FILENO) == -1) // Could be in a different function...
		{
			perror(NULL);
			exit(EXIT_FAILURE);
		}
		execvp(cmd_args[0], cmd_args); // We have to test if executable or not...
	}
	else
	{
		if (wait(&wstatus) == -1) // Could be in a different function...
			return (-1);
		if ((wstatus >> 8 & 0xFF) == EXIT_FAILURE)
			return (-1);
	}
	free(cmd_args); // Is it enough?
	return (0);
}
