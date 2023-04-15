/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_redirect_ex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:26:41 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/15 18:17:33 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

#define BUFFER_SIZE 50

int gpt_redirect(void)
{
    char 	*buffer;
    int 	fd[2];

	buffer = calloc(BUFFER_SIZE, sizeof(char));
    pipe(fd);
    if (fork() == 0) {
        close(fd[0]);
        printf("[child %i]\n", getpid());
		// fflush(stdout);
        dup2(fd[1], STDOUT_FILENO);
        printf("Hello, world!");
        close(fd[1]);
    } else {
		// wait(0);
        close(fd[1]);
        read(fd[0], buffer, 13);
        printf("[parent %i] '%s'\n\n", getpid(), buffer);
        close(fd[0]);
    }
    return 0;
}

int	my_redirect(void)
{
	pid_t	pid;
	int		fds[2];
	char	*buffer;

	// pid = fork(); // fork() before pipe() ? So each proc. has its own pipe?
	// how do they communicate then? Uh? Beware what you fork() with.
	if (pipe(fds) == -1)
		return (-1);
	pid = fork(); // before fork, processes has the same content. 
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
        printf("[child %i]\n", getpid());
		close(fds[0]); // The child inherits fds from its parents.
		dup2(fds[1], STDOUT_FILENO);
        printf("Hello, world!");
		close(fds[1]); // That's how piping becomes possible.
		// exit(EXIT_SUCCESS);
	}
	else
	{
		// wait(0);
		buffer = calloc(BUFFER_SIZE, sizeof(char));
		if (!buffer)
			return (-1);
		close(fds[1]);
		read(fds[0], buffer, 13);
        printf("[parent %i - buffer %p] '%s'\n", getpid(), buffer, buffer);
		free(buffer); // made pipe crash somehow? Depends where buffer is allocd
		close(fds[0]);
		// exit(EXIT_SUCCESS);
	}
	return (1);
}

int	main(void)
{
	gpt_redirect();
	my_redirect();
}