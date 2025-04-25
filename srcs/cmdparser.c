/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdenvmgr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:58:23 by jgermany          #+#    #+#             */
/*   Updated: 2025/04/25 19:03:14 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	cmpsr_set_prog_in(int i, char **argv, t_prg *prgs)
{
	if (i == 0)
	{
		prgs[i].in_fds[1] = -1;
		prgs[i].in_fds[0] = fmgr_open(argv[i], O_RDONLY, 0);
		if (prgs[i].in_fds[0] == -1 && fmgr_close(i, DIR_REV, prgs))
			return (-1);
		prgs[i].in_ty = CHT_REDR;
	}
	else
	{
		prgs[i].in_fds[0] = prgs[i - 1].out_fds[0];
		prgs[i].in_fds[1] = prgs[i - 1].out_fds[1];
		prgs[i].in_ty = prgs[i - 1].out_ty;
	}
	return (0);
}

static int	cmpsr_set_prog_out(int i, int argc, char **argv, t_prg *prgs)
{
	if (i == (argc - 2) - 1)
	{
		prgs[i].out_fds[0] = -1;
		prgs[i].out_fds[1] = fmgr_open(argv[argc - 1], NFILE_FLGS, NFILE_PERMS);
		if (prgs[i].out_fds[1] == -1 && fmgr_close(i, DIR_REV, prgs))
			return (-1);
		prgs[i].out_ty = CHT_REDR;
	}
	else
	{
		if (pipe(prgs[i].out_fds) == -1 && fmgr_close(i, DIR_REV, prgs))
			return (-1);
		prgs[i].out_ty = CHT_PIPE;
	}
	return (0);
}

int	cmpsr_parse_progs(int argc, char **argv, t_prg *prgs)
{
	int	i;

	i = -1;
	while (++i < (argc - 2))
	{
		prgs[i].cmd = argv[i + 1];
		if (cmpsr_set_prog_in(i, argv, prgs) == -1
			|| cmpsr_set_prog_out(i, argc, argv, prgs) == -1)
			return (-1);
	}
	prgs[i].cmd = NULL;
	return (0);
}
