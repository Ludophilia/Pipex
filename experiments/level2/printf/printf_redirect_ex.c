/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_redirect_ex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:26:41 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/15 16:03:21 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

#define BUFFER_SIZE 50

// Use the pipe, fork, dup, dup2 to redirect printf output to a buffer
// <child_p> <-------> <parent_p>

int gpt_redirect(void)
{
    int fd[2];
    char buffer[1024];

    pipe(fd);  // Create a pipe
    if (fork() == 0) {
        // Child process
		// printf("Child process:\n");
        close(fd[0]);  // Close the read end of the pipe
        dup2(fd[1], STDOUT_FILENO);  // Redirect stdout to the write end of the pipe
        fprintf(stdout, "Hello, world!\n");  // This will be written to the pipe
        close(fd[1]);  // Close the write end of the pipe
    } else {
        // Parent process
		// printf("Parent process:\n");
		// wait(0);
        close(fd[1]);  // Close the write end of the pipe
        read(fd[0], buffer, 15);  // Read from the pipe
        printf("[parent] '%s'\n", buffer);  // This will print "Hello, world!\n"
        close(fd[0]);  // Close the read end of the pipe
    }
    return 0;
}


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