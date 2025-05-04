/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:58:23 by jgermany          #+#    #+#             */
/*   Updated: 2025/05/04 17:08:31 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	cmpsr_set_prog_in(int i, char **argv, t_prg *prgs)
{
	if (i == 0)
	{
		prgs[i].in[1] = -1;
		prgs[i].in[0] = fmgr_open(argv[i], O_RDONLY, 0);
		if (prgs[i].in[0] == -1)
			return (-1);
		prgs[i].in_ty = CHTY_REDR;
	}
	else
	{
		prgs[i].in[0] = prgs[i - 1].out[0];
		prgs[i].in[1] = prgs[i - 1].out[1];
		prgs[i].in_ty = prgs[i - 1].out_ty;
	}
	return (0);
}

static int	cmpsr_set_prog_out(int i, int argc, char **argv, t_prg *prgs)
{
	if (i == (argc - 2) - 1)
	{
		prgs[i].out[0] = -1;
		prgs[i].out[1] = fmgr_open(argv[argc - 1], NWFL_FLGS, NWFL_PRMS);
		if (prgs[i].out[1] == -1)
			return (-1);
		prgs[i].out_ty = CHTY_REDR;
	}
	else
	{
		if (fmgr_pipe(prgs[i].out) == -1)
			return (-1);
		prgs[i].out_ty = CHTY_PIPE;
	}
	return (0);
}

int	cmpsr_parse_progs(int argc, char **argv, t_prg *prgs)
{
	int	i;

	i = -1;
	ft_memset(prgs, 0, PGRS_NBR * sizeof(t_prg));
	while (++i < (argc - 2))
	{
		prgs[i].cmd = argv[i + 1];
		if (cmpsr_set_prog_in(i, argv, prgs) == -1
			|| cmpsr_set_prog_out(i, argc, argv, prgs) == -1)
		{
			fmgr_close(i, DIR_REV, prgs);
			return (-1);
		}
	}
	prgs[i].cmd = NULL;
	return (0);
}
