/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdmgr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:39:20 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/22 14:13:54 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdmgr.h"

void	exec_cmd_with(t_cmd cmdenv, char **envp)
{
	char	**cmd_args;
	int		infd;
	int		outfd;

	// I will certainly move this somewhere else...	
	cmd_args = ft_split(cmdenv.cmd, '\x20');
	if (ft_strchr(cmd_args[0], '/') == NULL)
	{
		cmd_args[0] = search_executable(cmd_args[0], envp);
		if (cmd_args[0] == NULL)
		{
			errno = ENOENT;
			ft_dprintf(2, "pipex: command not found: '%s'\n", cmdenv.cmd);
			free_strs(cmd_args, 1);
			exit(EXIT_FAILURE);
		}
	}
	else if (check_perm(cmd_args[0], X_OK) == -1)
	{
		free_strs(cmd_args, 0);
		exit(EXIT_FAILURE);
	}

	// I will certainly move this somewhere else...	
	if (cmdenv.inf)
		infd = check_and_open(cmdenv.inf, R_OK, O_RDONLY);
	else if (cmdenv.outf)
		outfd = check_and_open(cmdenv.outf, W_OK, O_WRONLY);
	if (infd == -1 || outfd == -1)
		return (-1);
	
	// What about pipes?
		// One scenario is <file> <cmd> <pipe> OR <pipe> <cmd> <file>
		// Another scenario is <pipe> <cmd> <pipe>
		// How many pipe there is here at max? 2?


	if (!cmdenv.inf)
	{
		infd = cmdenv.pipe[0]
		
	}
		

	if (dup2(infd, 0) == -1 || dup2(outfd, 1) == -1 
		|| execve(cmd_args[0], cmd_args, envp) == -1)
	{
		perror("pipex");
		free_strs(cmd_args, 0);
		if (cmdenv.inf) // Why this condition?
			close(infd);
		else if (cmdenv.outf)
			close(outfd);
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

// Structure s_cmd / t_cmd

int	fork_and_exec(t_cmd cmdenv1, t_cmd cmdenv2, char **envp)
{
	int		pid_l;
	int		pid_r;
	int		ws_l;
	int		ws_r;

	// Before fork: 4 fds are open, and they will be inherited (all) by the 
	// child processes, even if you don't need them. Execve won't change
	// anything to this.

	// So be smart about which file descriptor you open and at what level...
	
	// Don't you see a pattern...?
	pid_l = fork();
	if (pid_l == -1)
		return (ft_perror(NULL, -1));
	else if (pid_l > 0)
	{
		pid_r = fork();
		if (pid_r == -1)
			return (ft_perror(NULL, -1));
	}

	// Don't you see a pattern...?
	if (pid_l == 0)
		exec_cmd_with(cmdenv1, envp); 
	else if (pid_r == 0)
		exec_cmd_with(cmdenv2, envp);

	// Don't you see a pattern...?
	if (pid_l > 0 && pid_r > 0)
	{
		// close(infd);
		// close(outfd);
		if (waitpid(pid_l, &ws_l, 0) == -1  || waitpid(pid_r, &ws_r, 0) == -1 
			|| (ws_r >> 8 & 0xFF) == EXIT_FAILURE
			|| (ws_l >> 8 & 0xFF) == EXIT_FAILURE)
			return (ft_perror(NULL, -1));
	}
	return (0);
}
