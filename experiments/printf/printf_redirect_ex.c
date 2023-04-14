/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:26:41 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/14 21:44:16 by jgermany         ###   ########.fr       */
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
	if (!pid)
	{
		printf("Child\n");
		// close(fds[0]);
		dup2(fds[1], 1);
		dprintf(1, "Test\n");
		
		read(fds[0], buffer, 4);
		printf("[Buffer] '%s'\n", buffer);
		close(fds[0]); //


		close(fds[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		wait(NULL);// WAIT IS NEEDED RIGHT 
		printf("Parent\n");
		close(fds[1]);
		read(fds[0], buffer, 4);
		printf("[Buffer] '%s'\n", buffer);
		close(fds[0]);
		exit(EXIT_SUCCESS);
	}
	free(buffer);
}