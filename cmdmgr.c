/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdmgr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:39:20 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/13 20:04:46 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdmgr.h"

void	free_args(char **cmd_args)
{
	char	**head;
	
	head = cmd_args;
	while (*head)
	{
		free(*head);
		head++;
	}
	free(cmd_args);
}

// Now. How to use execve instead of execvp?

// What's the problem. How to do that?

// - The problem lies in the first arg of execve and execvp. 
// 		- For execve, it's const char *pathname, the path to the file
//		to execute.
//
//		- For execvpe, it's const char *file. Execvpe search every directory 
//		in the colon separated list specified in the PATH environment variable
//		IF the specified filename DOES NOT contain a slash (/) character.

// - So...? We have to write something that will search PATH for the specified
// command if there is NO / is specified, starting with the current path maybe,
// as execve does it?

int	exec_cmd(char *cmd, int fd)
{
	int		pid;
	int		wstatus;
	char	**cmd_args;

	pid = fork();
	cmd_args = NULL;
	if (pid == -1)
	{
		perror(NULL);
		return (-1);
	}
	else if (pid == 0)
	{
		cmd_args = ft_split("beuarf", '\x20'); (void)cmd;// cmd missing
		if (dup2(fd, STDIN_FILENO) == -1 || execve(cmd_args[0], cmd_args, NULL)
			== -1)
		{
			free_args(cmd_args);
			perror(NULL);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (wait(&wstatus) == -1 || (wstatus >> 8 & 0xFF) == EXIT_FAILURE)
		{
			perror(NULL);	
			return (-1);
		}
	}
	return (0);
}
