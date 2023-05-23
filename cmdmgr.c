/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdmgr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:39:20 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/23 19:04:05 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdmgr.h"

void	exec_cmd_with(t_cmd cmdenv, char **envp)
{
	char	**cmd_args;
	int		infd;
	int		outfd;

	// Command part. I will certainly move this somewhere else...	
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

	// Pipe part. I will certainly move this somewhere else...
	// Smells like a function that takes pointers to fds as arguments...
	infd = 0;
	outfd = 0;
	if (cmdenv.mode == 0x0)
	{
		infd = cmdenv.files[0];
		outfd = cmdenv.pipes[1];

		close(cmdenv.files[1]);
		close(cmdenv.pipes[0]);
	}
	else if (cmdenv.mode == 0x2)
	{
		infd = cmdenv.pipes[0];
		outfd = cmdenv.files[1];

		close(cmdenv.pipes[1]);
		close(cmdenv.files[0]);
	}

	if (dup2(infd, 0) == -1 || dup2(outfd, 1) == -1 
		|| execve(cmd_args[0], cmd_args, envp) == -1)
	{
		perror("pipex");
		free_strs(cmd_args, 0);
		close(infd);
		close(outfd);
		exit(EXIT_FAILURE);
	}
}

int	fork_and_exec(t_cmd cmdenv1, t_cmd cmdenv2, char **envp)
{
	// Don't you see a pattern...?
	int		pid_l;
	int		pid_r;
	int		ws_l;
	int		ws_r;

	// Don't you see a pattern...?
	pid_l = fork();
	if (pid_l == -1)
		return (ft_perror(-1, NULL));
	else if (pid_l > 0)
	{
		pid_r = fork();
		if (pid_r == -1)
			return (ft_perror(-1, NULL));
	}

	// Don't you see a pattern...?
	if (pid_l == 0)
		exec_cmd_with(cmdenv1, envp); 
	else if (pid_r == 0)
		exec_cmd_with(cmdenv2, envp);

	// Don't you see a pattern...?
	if (pid_l > 0 && pid_r > 0)
	{
		close(cmdenv1.pipes[1]);
		close(cmdenv1.pipes[0]); 
		if (waitpid(pid_l, &ws_l, 0) == -1  || waitpid(pid_r, &ws_r, 0) == -1 
			|| (ws_r >> 8 & 0xFF) == EXIT_FAILURE
			|| (ws_l >> 8 & 0xFF) == EXIT_FAILURE)
			return (ft_perror(-1, NULL));
	}
	return (0);
}
