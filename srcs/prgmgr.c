/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prgmgr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:39:20 by jgermany          #+#    #+#             */
/*   Updated: 2025/05/12 20:17:03 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// 23/04 - Too complicated, not ereganto
int	pgm_free_strs(char **strs, int offset)
{
	char	**head;

	if (strs == NULL)
		return (-1);
	head = strs + offset;
	while (*head)
	{
		free(*head);
		head++;
	}
	free(strs);
	return (1);
}

// 12/05 - Ok, those two are pretty much what's left to do...
static int	pgm_wait_cmds(t_cmd *cmdenvs, int i)
{
	int	ws;
	int	fails;

	ws = -1;
	fails = 0;
	while (--i >= 0)
	{
		if (waitpid(cmdenvs[i].pid, &ws, 0) == -1
			|| (ws >> 8 & 0xFF) == EXIT_FAILURE)
				fails++;
	}
	if (fails > 0)
		return (-1);
	return (0);
}

static int	pgm_exec_cmd(t_prg *prgs, int i, char **envp)
{
	char	**cmd_args;

	cmd_args = ft_split(prgs[i].cmd, ' ');
	if (cmd_args == NULL 
		|| (*cmd_args == NULL && ft_eprintf(ERR_CMD, NULL))
		|| ptb_check_path(cmd_args, prgs, i, envp) == -1
		|| dup2(prgs[i].in[0], 0) == -1
		|| dup2(prgs[i].out[1], 1) == -1)
	{
		pgm_free_strs(cmd_args, 0);
		fmg_closeall(0, DIR_FWD, prgs);
		return (-1);
	}
	if (fmg_closeall(0, DIR_FWD, prgs) == -1
		|| execve(*cmd_args, cmd_args, envp) == -1)
	{
		pgm_free_strs(cmd_args, 0);
		return (-1);
	}
	return (0);
}

// 12/05 = I'll stop printing on stderr most errors, only the most important ones... 
int	pgm_exec_progs(t_prg *prgs, char **envp)
{
	pid_t	pid;
	int		i;

	i = -1;
	while (prgs[++i].cmd)
	{
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0 && pgm_exec_cmd(prgs, i, envp) == -1)
			exit(EXIT_FAILURE);
		prgs[i].pid = pid;
		if (fmg_close(prgs[i].in, 0) == -1 || fmg_close(prgs[i].out, 1) == -1)
			return (-1);
	}
	if (pgm_wait_cmds(prgs, i) == -1)
		return (-1);
	return (0);
}
