/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdmgr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:39:20 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/21 17:12:55 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdmgr.h"

void	exec_with(t_cmd cmdenv, char **envp)
{
	char	**cmd_args;

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
	if (dup2(cmdenv.infd, 0) == -1 || dup2(cmdenv.outfd, 1) == -1 
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

// Structure s_cmd / t_cmd

int	fork_and_exec(t_cmd cmdenv1, t_cmd cmdenv2, char **envp)
{
	int		pid_l;
	int		pid_r;
	int		ws_l;
	int		ws_r;

	// Don't you see a pattern...?
	pid_l = fork();
	if (pid_l == -1)
		return (ft_perror(NULL));
	else if (pid_l > 0)
	{
		pid_r = fork();
		if (pid_r == -1)
			return (ft_perror(NULL));
	}

	// Don't you see a pattern...?
	if (pid_l == 0)
		exec_with(cmdenv1, envp); 
	else if (pid_r == 0)
		exec_with(cmdenv2, envp);


	// Don't you see a pattern...?
	if (pid_l > 0 && pid_r > 0)
	{
		// close(infd);
		// close(outfd);
		if (waitpid(pid_l, &ws_l, 0) == -1  || waitpid(pid_r, &ws_r, 0) == -1 
			|| (ws_r >> 8 & 0xFF) == EXIT_FAILURE
			|| (ws_l >> 8 & 0xFF) == EXIT_FAILURE)
			return (ft_perror(NULL));
	}
	return (0);
}
