/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_ex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 20:06:01 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/25 19:51:41 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

/* Level0 - Let's understand how wait works with a simple example. 
For reference, waitpid(2) option WNOHANG makes waitpid() check if a child
process exits and return 0 IMMEDIATELY if so. Option WUNTRACED make waitpid()
return if its child has been paused with a SIGSTOP signal. Option WCONTINUED
make waitpid() return if its child has been resumed with a SIGCONT signal. */
int	wait_level0(unsigned keep_alive)
{
	pid_t	pid;
	int		wstatus;
	pid_t	wait_ret;

	if (!keep_alive)
		return (0);
	printf("[PID %i] wait_level0() starts! fork() is coming!\n", getpid());
	pid = fork();
	if (pid == -1)
		return (-1);
	if (!pid)
	{
		while (keep_alive)
		{
			printf("[PID %i [PPID %i]] About to get out of "
				"child process in %u...\n", getpid(), getppid(), keep_alive--);
			usleep(1000000);
		}
		exit(25); // 25 is the exit status btw
	}
	else
	{	
		wait_ret = waitpid(pid, &wstatus, 0); // wait(&wstatus) if options=0
		if (wait_ret == -1) 
			return (-1);
		printf("[PID %i] In parent process with wstatus = %i and wait_ret"
			" of %i!\n", getpid(), wstatus, wait_ret);
		printf("[PID %i] WIFEXITED returned %s\n", getpid(),
			(char *[]){"false", "true"}[WIFEXITED(wstatus)]);
		printf("[PID %i] Exit status or WEXITSTATUS: %i\n",
			getpid(), WEXITSTATUS(wstatus));
		printf("[PID %i] WIFSIGNALED returned %s\n", getpid(),
			(char *[]){"false", "true"}[WIFSIGNALED(wstatus)]);
		printf("[PID %i] Terminating Signal or WTERMSIG: %i\n",
			getpid(), WTERMSIG(wstatus));
	}
	printf("[PID %i] wait_level0() is reaching its end!\n", getpid());
	return (0);
}

/* Level1 - Can we alternate calls between the parent process and its child? 
Certainly, but we will have to use signals with raise(2) SIGSTOP (child) 
and kill(2) with SIGCONT (18) (parent). And waitpid(2) will have to use 
the WUNTRACED option that make it return if its child has been paused with a
SIGSTOP signal... */
int	wait_pong_lv1(unsigned keep_alive)
{
	pid_t	pid;
	int		wstatus;

	if (!keep_alive)
		return (0);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (!pid)
	{
		while (keep_alive)
		{
			printf("[PID %i, PPID %i] Getting out of child process in %u...\n",
				getpid(), getppid(), keep_alive--);
			if (keep_alive)
				printf("[PID %i, PPID %i] But first, why not SIGSTOP "
				"ourselves? 😨\n", getpid(), getppid());
			sleep(1);
			raise(SIGSTOP); // Eq to kill(getpid(), SIGSTOP)
		}
		printf("[PID %i, PPID %i] End of child process !\n", getpid(),
			getppid());
	}
	else
	{	
		if (waitpid(pid, &wstatus, WUNTRACED) == -1)
			return (-1);
		while (WSTOPSIG(wstatus) == SIGSTOP)
		{
			printf("[PID %i, PPID %i] In parent process! Sending SIGCONT to "
			"child process...\n", getpid(), getppid());
			sleep(1);
			kill(pid, SIGCONT);
			if (waitpid(pid, &wstatus, WUNTRACED) == -1)
				return (-1);
		}
		printf("[PID %i, PPID %i] End of parent process !\n", getpid(),
			getppid());
	}
	return (0);
}

int	main(void)
{
	if (wait_level0(0) == -1)
		return (-1);
	if (wait_pong_lv1(3) == -1)
		return (-1);
	return (0);
}
