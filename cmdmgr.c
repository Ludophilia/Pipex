/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdmgr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:39:20 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/21 14:25:50 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdmgr.h"

void	exec_cmd(char *cmd, int infd, int outfd, char **envp)
{
	char	**cmd_args;

	cmd_args = ft_split(cmd, '\x20');
	if (ft_strchr(cmd_args[0], '/') == NULL)
	{
		cmd_args[0] = search_executable(cmd_args[0], envp);
		if (cmd_args[0] == NULL)
		{
			errno = ENOENT;
			ft_dprintf(2, "pipex: command not found: '%s'\n", cmd);
			free_strs(cmd_args, 1);
			exit(EXIT_FAILURE);
		}
	}
	else if (check_perm(cmd_args[0], X_OK) == -1)
	{
		free_strs(cmd_args, 0);
		exit(EXIT_FAILURE);
	}
	if (dup2(infd, 0) == -1 || dup2(outfd, 1) == -1 
		|| execve(cmd_args[0], cmd_args, envp) == -1)
	{
		perror("pipex");
		free_strs(cmd_args, 0);
		exit(EXIT_FAILURE);
	}
}

// move R_OK, O_RDONLY in the args in a struct or something

// A command:
//	- READS from an INFILE or a PIPE
// 	- WRITE to an OUTFILE or a PIPE

// A command always has context, symbolized by its fds...
// So the problem is how to create that context

// To get fds you need to:
//	-- open files (with modes) 
//	-- open pipes
// Where do I need to open those files or pipes?
//	-- Here ?
//		-- We just fork and exec, 
	
int	fork_and_exec(char *cmd, int infd, int outfd, char **envp)
{
	int		pid_l;
	int		pid_r;
	int		wstatus_l;
	int		wstatus_r;

	pid_l = fork();
	if (pid_l == -1)
	{
		perror(NULL);
		return (-1);
	}
	else if (pid_l > 0)
	{
		pid_r = fork();
		if (pid_r == -1)
		{
			perror(NULL);
			return (-1);
		}
	}
	if (pid_l == 0)
	{
		exec_cmd(cmd, infd, outfd, envp); 
	}
	else if (pid_r == 0)
	{
		exec_cmd(cmd, infd, outfd, envp);
	}
	if (pid_l > 0 && pid_r > 0)
	{
		close(infd); // HERE??? 
		close(outfd); // REALLY???
		if (waitpid(pid_l, &wstatus_l, 0) == -1 
			|| waitpid(pid_r, &wstatus_r, 0) == -1 
			|| (wstatus_r >> 8 & 0xFF) == EXIT_FAILURE
			|| (wstatus_l >> 8 & 0xFF) == EXIT_FAILURE)
		{
			perror(NULL);
			return (-1);
		}
	}
	return (0);
}
