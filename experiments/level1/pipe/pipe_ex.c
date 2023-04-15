/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_redirect_ex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:26:41 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/15 13:49:33 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

#define BUFFER_SIZE 50

// Use the pipe, fork, dup, dup2 to redirect printf output to a buffer
// <child_p> <-------> <parent_p>
int	main(void)
{
	int		fds[2];
	int		stdout_fd;
	pid_t	pid;
	char	*buffer;

	pid = fork();
	buffer = calloc(BUFFER_SIZE, sizeof(char));
	if (!buffer || pipe(fds) == -1 || pid == -1)
		return (1);
	
	if (!pid)
	{
		// printf("Child: fds[0] = %i, fds[1] = %i\n", fds[0], fds[1]);
		// close(fds[0]);
		stdout_fd = dup(STDOUT_FILENO);
		dup2(fds[1], STDOUT_FILENO);
		// dprintf(STDOUT_FILENO, "Test\n");
		// printf("Test\n");
		write(STDOUT_FILENO, "test", 4);
		// write(fds[1], "test", 4);

		dup2(stdout_fd, 1);
		// fprintf(stderr, "[Buffer C] '%s'\n", buffer);

		if (read(fds[0], buffer, 4) == 0)
			exit(EXIT_FAILURE);
		printf("[Buffer] '%s'\n", buffer);
		close(fds[0]);
		close(fds[1]);

		exit(EXIT_SUCCESS);
	}
	else
	{
		wait(0);// I still don't understand how this works
		// printf("Parent: fds[0] = %i, fds[1] = %i\n", fds[0], fds[1]);
		close(fds[1]);
		lseek(fds[0], 0, SEEK_SET);
		read(fds[0], buffer, 4);
		printf("[Buffer P] '%s'\n", buffer);
		close(fds[0]);
		exit(EXIT_SUCCESS);
	}
	free(buffer);
}