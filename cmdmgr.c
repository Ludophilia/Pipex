/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdmgr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:39:20 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/14 17:30:01 by jgermany         ###   ########.fr       */
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

// How to use execve instead of execvp? 

// What's the problem.

// - The problem lies in the difference of first arg in execve and execvp.
// 		- For `int execve(const char *pathname, char *const argv[],
// 		char *const envp[])`, it's `pathname`, the path to the file to execute.
//		- For `int execvpe(const char *file, char *const argv[],
//		char *const envp[])`, it's `file`, a file that execvpe will search in
//		every directory specified in the PATH environment variable,
//		a the colon-separated list of directories, IF the specified filename
//		DOES NOT contain a slash (/) character.

// - So...? We have to write something that will search PATH for the specified
// command if :
//		- There is NO `/` in pathname (including for cmds that are in the 
//		current PATH which are invoked via their full path, either via `./cmd`
//		or `$PWD/cmd` or `/root/project/Pipex/cmd` by ex...)
//		- 
// 
//	and return the path to that command so that execve can execute it...

// OK, and how to do it?

//		- How to check if argv[2] contains `/` or not?
//		- How do I get from PATH every dirs from where I need to search cmd ?
//		- How to search for the file in every dir?
//			- 


//		- How do I make the match?

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
		cmd_args = ft_split("./beuarf", '\x20'); (void)cmd;// cmd missing
		if (dup2(fd, STDIN_FILENO) == -1 || execvp(cmd_args[0], cmd_args)
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
