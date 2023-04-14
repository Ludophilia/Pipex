/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_redirect_ex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:26:41 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/15 00:45:31 by jgermany         ###   ########.fr       */
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
	pid_t	pid;
	char	*buffer;

	pid = fork();
	buffer = calloc(BUFFER_SIZE, sizeof(char));
	if (!buffer || pipe(fds) == -1 || pid == -1)
		return (1);
	
	buffer = "WOW";
	if (!pid)
	{
		printf("Child: fds[0] = %i, fds[1] = %i\n", fds[0], fds[1]);
		close(fds[0]);
		dup2(fds[1], 1);
		dprintf(1, "Test\n");
		printf("[Buffer C] '%s'\n", buffer);

		// read(fds[0], buffer, 4);
		// printf("[Buffer] '%s'\n", buffer);
		// close(fds[0]);

		close(fds[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		wait(NULL);// I still don't understand how this works
		printf("Parent: fds[0] = %i, fds[1] = %i\n", fds[0], fds[1]);
		close(fds[1]);
		lseek(fds[0], 0, SEEK_SET);
		read(fds[0], buffer, 4);
		printf("[Buffer P] '%s'\n", buffer);
		close(fds[0]);
		exit(EXIT_SUCCESS);
	}
	free(buffer);
}