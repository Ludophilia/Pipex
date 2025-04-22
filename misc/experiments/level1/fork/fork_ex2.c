/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_ex2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 11:31:52 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/27 15:52:25 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

// WHAT DO YOU WANT TO DO? 
// 	- store the pid of each fork in the same array
//	- understand how each process see the array
// 	- trigger a fork based on the content of this array
void	init_pids(pid_t *pids, int value, int len)
{
	int		head;

	head = -1;
	while (++head < len)
		pids[head] = value;
}

int	is_parent(pid_t *pids, int len)
{
	int	head;

	head = -1;
	while (++head < len)
	{
		if (pids[head] == 0)
			return (0);
	}
	return (1);
}

// NOTE - Each process has its own pids array, inherited from its parent at 
// fork() time. That explains why some values are unintialized compared to the 
// parent pid array... and why some child PID are visible to other child
// processes. WHAT'S REALLY INTERESTING however is that the 0 symbolizing a
// a child process from the child process point of view only appear once per
// pid array, making some operations possible.
//		[259976, 259977, 259978...] (Master Process POV)
//		[259976, 0, -2...] (Child Process POV)
int	main(int argc, char **argv)
{
	pid_t	pids[BUFFER_SIZE];
	int		len;
	int		head;

	if (argc != 2)
		return (1);
	len = 0;
	init_pids(pids, -2, BUFFER_SIZE);
	while (len < atoi(argv[1]))
	{
		if (len == 0 || is_parent(pids, len))
		{
			pids[len] = fork();
			if (pids[len] == -1)
				return (1);
		}
		len++;
	}
	head = -1;
	while (++head < len)
		printf("[%i (%i)] pids[%i] = %i\n", getpid(), getppid(),
			head, pids[head]);

	return (0);
}
