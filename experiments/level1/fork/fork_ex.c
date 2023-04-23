/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_ex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 14:14:50 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/23 22:50:10 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/* Level0 - Simple call to fork to understand what's happening. Don't hesitate
to ps(1) the shit out of it, then kill it will kill -TERM <pid> */
int	fork_level0(unsigned keep_alive)
{
	pid_t	pid;

	if (!keep_alive)
		return (0);
	pid = fork(); 
	if (pid == -1)
		return (-1);
	if (pid == 0)
		printf("[PID: %i] Child Process\n", getpid());
	else
		printf("[PID: %i] Parent Process\n", getpid());
	pause();
	return (0);
}

/* Level2 - What happens when multiple fork() syscalls are made? */
/// Yeah... We'll se that at a later date maybe?

int	main(void)
{
	if (fork_level0(1) == -1)
		return (-1);
	return (0);
}
