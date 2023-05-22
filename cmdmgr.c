/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdmgr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:39:20 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/22 19:53:44 by jgermany         ###   ########.fr       */
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
	// < file1 and > file2. file1 and file2 should be created right?
	// Maybe doing this at this level explains why the prompt is not
	// given back...
	if (cmdenv.mode == 0x0)
	{
		infd = check_and_open((char *)(cmdenv.inf), R_OK, O_RDONLY);
		if (infd == -1)
			exit(EXIT_FAILURE);
	}
	else if (cmdenv.mode == 0x2)
	{
		outfd = check_and_open((char *)(cmdenv.outf), W_OK, O_WRONLY);
		if (outfd == -1)
			exit(EXIT_FAILURE);
	}

	// What about pipes?
		// The command above matches <file> <cmd> <pipe> OR <pipe> <cmd> <file>
		// Another scenario is <pipe> <cmd> <pipe>
		// So how many pipe there is here at max? 2?

	// So what to do with those pipes now ?
	// Associate them with infd or outfd. // Close those who are not used.
	if (cmdenv.mode == 0x0)
	{
		outfd = ((int *)cmdenv.outf)[1];
		close(((int *)cmdenv.outf)[0]);
	}
	else if (cmdenv.mode == 0x2)
	{
		infd = ((int *)cmdenv.inf)[0];
		close(((int *)cmdenv.inf)[1]);
	}

	// ft_dprintf(1, "mode: %x - infd: %i, outfd: %i\n", cmdenv.mode, infd, outfd);
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
	int		pid_l;
	int		pid_r;
	int		ws_l;
	int		ws_r;
	int		fds[2];

	// So be smart about which file descriptor you open and at what level...
	 // MUST BE AT PARENT LEVEL (BRIDGE BETWEEN PROCESSES)
	if (pipe(fds) == -1)
		return (ft_perror(-1, NULL));
	if (cmdenv1.mode == 0x0)
		cmdenv1.outf = fds;
	if (cmdenv2.mode == 0x2)
		cmdenv2.inf = fds;

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
		// close(infd);
		// close(outfd);
		if (waitpid(pid_l, &ws_l, 0) == -1  || waitpid(pid_r, &ws_r, 0) == -1 
			|| (ws_r >> 8 & 0xFF) == EXIT_FAILURE
			|| (ws_l >> 8 & 0xFF) == EXIT_FAILURE)
			return (ft_perror(-1, NULL));
	}
	return (0);
}
