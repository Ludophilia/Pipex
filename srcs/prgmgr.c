/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prgmgr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:39:20 by jgermany          #+#    #+#             */
/*   Updated: 2025/05/04 18:53:06 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	wait_cmds(t_cmd *cmdenvs, int head)
{
	int		ws;
	int		fails;

	ws = -1;
	fails = 0;
	while (--head >= 0)
	{
		if (waitpid(cmdenvs[head].pid, &ws, 0) == -1
			|| (ws >> 8 & 0xFF) == EXIT_FAILURE)
				fails++;
	}
	if (fails > 0)
		return (-1);
	return (0);
}

static void	resolve_cmdpath(char **cmd_args, t_cmd *cmdenvs, int head,
char **envp)
{
	char	*orig_cmd;

	orig_cmd = ft_strdup(cmd_args[0]);
	cmd_args[0] = search_executable(cmd_args[0], envp);
	if (cmd_args[0] == NULL)
	{
		errno = ENOENT;
		ft_eprintf("pipex: %s: command not found\n", orig_cmd);
		free(orig_cmd);
		free_strs(cmd_args, 1);
		// close_fds(cmdenvs, head, 0);
		fmgr_close(head, DIR_FWD, cmdenvs);
		exit(EXIT_FAILURE);
	}
}

static char	**split_cmd(t_cmd *cmdenvs, int head, char **envp)
{
	char	**cmd_args;

	cmd_args = ft_split(cmdenvs[head].cmd, '\x20');
	if (cmd_args[0] == NULL)
	{
		errno = EINVAL;
		ft_eprintf("pipex: %s: command not found\n", NULL);
		free_strs(cmd_args, 0);
		// close_fds(cmdenvs, head, 0);
		fmgr_close(head, DIR_FWD, cmdenvs);
		exit(EXIT_FAILURE);
	}
	else if (ft_strchr(cmd_args[0], '/') == NULL)
		resolve_cmdpath(cmd_args, cmdenvs, head, envp);
	else if (check_perm(cmd_args[0], X_OK) == -1)
	{
		free_strs(cmd_args, 0);
		// close_fds(cmdenvs, head, 0);
		fmgr_close(head, DIR_FWD, cmdenvs);
		exit(EXIT_FAILURE);
	}
	return (cmd_args);
}

static void	exec_cmd(t_cmd *cmdenvs, int head, char **envp)
{
	char	**cmd_args;
	int		infd;
	int		outfd;

	cmd_args = split_cmd(cmdenvs, head, envp);
	infd = cmdenvs[head].in[0];
	outfd = cmdenvs[head].out[1];
	if (dup2(infd, 0) == -1 || dup2(outfd, 1) == -1)
	{
		perror("pipex");
		free_strs(cmd_args, 0);
		// close_fds(cmdenvs, head, 0);
		fmgr_close(head, DIR_FWD, cmdenvs);
		exit(EXIT_FAILURE);
	}
	// close_fds(cmdenvs, head, 0);
	fmgr_close(head, DIR_FWD, cmdenvs);
	if (execve(cmd_args[0], cmd_args, envp) == -1)
	{
		perror("pipex");
		free_strs(cmd_args, 0);
		exit(EXIT_FAILURE);
	}
}

// 5/05 - Next, exec_cmd and wait_cmds
int	prgmgr_exec_progs(t_prg *prgs, char **envp)
{
	pid_t	pid;
	int		i;

	i = -1;
	while (prgs[++i].cmd)
	{
		pid = fork();
		if (pid == -1 && ft_eprintf(ERR_GENERIC, strerror(errno)))
			return (-1);
		if (pid == 0)
			exec_cmd(prgs, i, envp);
		if (close(prgs[i].in[0]) == -1 || close(prgs[i].out[1]) == -1)
		{
			ft_eprintf(ERR_GENERIC, strerror(errno));
			return (-1);
		}
		prgs[i].pid = pid;
	}
	if (wait_cmds(prgs, i) == -1)
		return (-1);
	return (0);
}
