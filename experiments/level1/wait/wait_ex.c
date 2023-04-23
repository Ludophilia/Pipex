/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_ex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 20:06:01 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/23 22:51:55 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/* Level0 - Let's understand how wait works with a simple example. */
int	wait_level0(unsigned keep_alive)
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
			printf("Getting out of child process [PID: %i] in %u...\n",
				getpid(), keep_alive--);
			usleep(1000000);
		}
		exit(25);
	}
	else
	{	
		if (wait(&wstatus) == -1)
			return (-1);
		printf("In parent process [PID: %i] with wstatus %i!\n",
			getpid(), wstatus);
		printf("WIFEXITED returns %s\n",
			(char *[]){"false", "true"}[WIFEXITED(wstatus)]);
		printf("Exit status: %i\n", WEXITSTATUS(wstatus)); // Default 0
		printf("WIFSIGNALED  returns %s\n",
			(char *[]){"false", "true"}[WIFSIGNALED(wstatus)]);
		printf("Terminating Signal: %i\n", WTERMSIG(wstatus)); // Default 0

	}
	return (0);
}

/* Level1 - Can we alternate calls between the parent process and its child? 
Certainly, but we will have to use signals with pause(2) and kill(2) */
// int	wait_level1(unsigned keep_alive)
// {
// 	pid_t	pid;
// 	int		wstatus;

// 	if (!keep_alive)
// 		return (0);
// 	pid = fork();
// 	if (pid == -1)
// 		return (-1);
// 	if (!pid)
// 	{
// 		while (keep_alive)
// 		{
// 			printf("Keeping out of child process [PID: %i] in %u...\n",
// 				getpid(), keep_alive--);
// 			// pause();
// 			usleep(1000000);
// 		}
// 	}
// 	else
// 	{	
// 		if (waitpid(pid, NULL) == -1)
// 			return (-1);
// 		printf("In parent process [PID: %i]!\n", getpid());
// 	}
// 	return (0);
// }

/* Level2 - Can we alternate calls between the parent process and its child? 
Why not use wait? It's still not working as expected though: The following 
version calls  every child process' printf before calling every parent 
process' ones */

// /* Level3 - So how can we alternate calls between the parent process 
// and its child? Why not use wait? */
// int	fork_level3(unsigned keep_alive)
// {
// 	pid_t	pid;
// 	int		wstatus;

// 	if (!keep_alive)
// 		return (0);
// 	pid = fork();
// 	if (pid == -1)
// 		return (-1);
// 	while (keep_alive--)
// 	{
// 		if (!pid)
// 		{
// 			printf("Child process: [PID]%i\n", getpid());		
// 		}
// 		else
// 		{
// 			wait(&wstatus);
// 			printf("Parent process: [PID: %i], wstatus: %i\n\n",
// 				getpid(), wstatus);
// 		}
// 		sleep(1);
// 	}
// 	return (0);
// }

int	main(void)
{
	if (wait_level0(3) == -1)
		return (-1);
	// if (wait_level1(1) == -1)
	// 	return (-1);
	return (0);
}
