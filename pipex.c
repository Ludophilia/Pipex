/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:45:09 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/11 23:21:24 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Project goal - create pipex, a program that simulates the behavior
// of unix pipes...

// Let's manage < file1 cmd1 first


#include "pipex.h"


int		exec_cmd(char **path, )
{
	int		pid;
	int		wstatus;
	char	**cmd;

	cmd = ft_split(argv[2], '\x20'); // LEAK?
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror(NULL);
			exit(EXIT_FAILURE);
		}
		execvp(cmd[0], cmd); // We have to test if executable or not...
	}
	else
	{
		if (wait(&wstatus) == -1)
			return (1);
		if ((wstatus >> 8 & 0xFF) == EXIT_FAILURE)
			return (1);
	}
	close(fd);
	free(cmd); // Is it enough?
}

int		main(int argc, char **argv)
{


	if (check_args(argc, argv) == -1)
		return (1);

	// Doesn't work anymore



	return (0);
}
