/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:45:09 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/11 18:29:25 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Project goal - create pipex, a program that simulates the behavior
// of unix pipes...

#include "pipex.h"

int		check_perm(char *filename, int mode)
{
	if (access(filename, mode) == -1) 
	{
		perror(filename);
		return (-1);
	}
	return (0);
}

// Let's manage < file1 cmd1.
int		main(int argc, char **argv)
{
	int		fd;
	int		pid;
	int		wstatus;
	char	**cmd;

	if (argc != 3)
	{
		errno = EINVAL;
		perror("pipex");
		ft_dprintf(2, "usage: pipex <file1> <cmd1> <cmd2> <file2>\n");
		return (1);
	}
	if (check_perm(argv[1], F_OK) == -1 || check_perm(argv[1], R_OK) == -1)
		return (1);
	// What do you do next?

	// open the file to read, get a file descriptor
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (1);

	// dup or dup2 into a the child process, so that the process reads the
	// fd instead of dup2().
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

	return (0);
}
