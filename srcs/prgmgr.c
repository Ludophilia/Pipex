/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prgmgr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:39:20 by jgermany          #+#    #+#             */
/*   Updated: 2025/05/12 21:14:06 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pgm_free_strs(char **strs, int offset)
{
	int	i;

	if (strs == NULL)
		return (-1);
	i = 0;
	while (strs[i] + offset)
		free(strs[i++]);
	free(strs);
	return (1);
}

static int	pgm_wait_cmds(t_prg *prgs, int i)
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
