/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prgmgr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:39:20 by jgermany          #+#    #+#             */
/*   Updated: 2025/05/23 11:56:28 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pgm_free_strs(int from_id, char **strs)
{
	int	i;

	if (strs == NULL)
		return (-1);
	i = 0;
	while (strs[from_id + i])
		free(strs[from_id + i++]);
	free(strs);
	return (1);
}

static int	pgm_wait_cmds(int i, t_prg *prgs)
{
	int	wait_stat;
	int	chld_fails;

	chld_fails = 0;
	while (--i >= 0)
	{
		if (waitpid(prgs[i].pid, &wait_stat, 0) == -1
			|| ((wait_stat >> 8) & 0xFF) == EXIT_FAILURE)
			++chld_fails;
	}
	if (chld_fails != 0)
		return (-1);
	return (0);
}

static int	pgm_exec_cmd(t_prg *prgs, int i, char **envp)
{
	char	**cmd_args;

	cmd_args = ft_split(prgs[i].cmd, ' ');
	if (cmd_args == NULL
		|| (*cmd_args == NULL && ft_eprintf(ERR_CMD, NULL))
		|| ptb_check_path(cmd_args, envp) == -1
		|| dup2(prgs[i].in[0], 0) == -1
		|| dup2(prgs[i].out[1], 1) == -1)
	{
		pgm_free_strs(0, cmd_args);
		fmg_closeall(0, DIR_FWD, prgs);
		return (-1);
	}
	if (fmg_closeall(0, DIR_FWD, prgs) == -1
		|| execve(*cmd_args, cmd_args, envp) == -1)
	{
		pgm_free_strs(0, cmd_args);
		return (-1);
	}
	return (0);
}

int	pgm_exec_progs(t_prg *prgs, char **envp)
{
	pid_t	pid;
	int		i;

	i = -1;
	while (prgs[++i].cmd)
	{
		pid = fork();
		if (pid == -1 && ft_eprintf(ERR_GNR, strerror(errno)))
		{
			fmg_closeall(0, DIR_FWD, prgs);
			pgm_wait_cmds(i, prgs);
			return (-1);
		}
		if (pid == 0 && pgm_exec_cmd(prgs, i, envp) == -1)
			exit(EXIT_FAILURE);
		prgs[i].pid = pid;
	}
	if (fmg_closeall(0, DIR_FWD, prgs) && pgm_wait_cmds(i, prgs) == -1)
		return (-1);
	return (0);
}
