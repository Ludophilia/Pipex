/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_ex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 14:14:50 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/25 16:42:08 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/* Level0 - Simple call to fork to understand what's happening. Don't hesitate
to ps(1) the shit out of it, then kill it will kill -TERM <pid> */
int	fork_level0(unsigned keep_alive, int wait_child)
{
	pid_t	pid;

	if (!keep_alive)
		return (0);
	printf("[PID %i (PPID %i)] fork_level0() starts! fork() is coming!\n",
		getpid(), getppid());
	pid = fork(); 
	if (pid == -1)
		return (-1);
	if (pid == 0)
		printf("[PID %i (PPID %i)] Child process exclusive statement\n",
			getpid(), getppid());
	else
	{
		if (wait_child)
		{
			wait(NULL);
			printf("[PID %i (PPID %i)] Waited for child to finish execution\n",
				getpid(), getppid());
		}
		printf("[PID %i (PPID %i)] Parent process exclusive statement\n",
			getpid(), getppid());
	}
	printf("[PID %i (PPID %i)] fork_level0() is about to end, "
		"just %i secs...\n", getpid(), getppid(), keep_alive);
	sleep(keep_alive);
	return (0);
}

/* Level1 - What happens when multiple fork() syscalls are made? */
/// Yeah... We'll se that at a later date maybe?

int	main(void)
{
	printf("[PID %i (PPID %i)] main() starts!\n", getpid(), getppid());
	if (fork_level0(3, 1) == -1)
		return (-1);
	printf("[PID %i (PPID %i)] main() is about to end.\n", getpid(), getppid());
	return (0);
}
