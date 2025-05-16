/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:58:23 by jgermany          #+#    #+#             */
/*   Updated: 2025/05/16 20:20:42 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	psrb_set_prog_in(int prg_id, char **argv, t_prg *prgs)
{
	if (prg_id == 0)
	{
		prgs[prg_id].in[1] = -1;
		prgs[prg_id].in[0] = fmgb_open(argv[prg_id], O_RDONLY, 0);
		if (prgs[prg_id].in[0] == -1)
			return (-1);
		prgs[prg_id].in_ty = CHTY_REDR;
	}
	else
	{
		prgs[prg_id].in[0] = prgs[prg_id - 1].out[0];
		prgs[prg_id].in[1] = prgs[prg_id - 1].out[1];
		prgs[prg_id].in_ty = prgs[prg_id - 1].out_ty;
	}
	return (0);
}

static int	psrb_set_prog_out(int prg_id, int argc, char **argv, t_prg *prgs)
{
	if (prg_id == (argc - 2) - 1)
	{
		prgs[prg_id].out[0] = -1;
		prgs[prg_id].out[1] = fmgb_open(argv[argc - 1], NWFL_FLGS, NWFL_PRMS);
		if (prgs[prg_id].out[1] == -1)
			return (-1);
		prgs[prg_id].out_ty = CHTY_REDR;
	}
	else
	{
		if (fmgb_pipe(prgs[prg_id].out) == -1)
			return (-1);
		prgs[prg_id].out_ty = CHTY_PIPE;
	}
	return (0);
}

int	psrb_parse_progs(int argc, char **argv, t_prg *prgs)
{
	int	prg_id;

	prg_id = -1;
	ft_memset(prgs, 0, PGRS_NBR * sizeof(t_prg));
	while (++prg_id < (argc - 2))
	{
		prgs[prg_id].cmd = argv[1 + prg_id];
		if (psrb_set_prog_in(prg_id, argv, prgs) == -1
			|| psrb_set_prog_out(prg_id, argc, argv, prgs) == -1)
		{
			fmgb_closeall(prg_id, DIR_REV, prgs);
			return (-1);
		}
	}
	prgs[prg_id].cmd = NULL;
	return (0);
}
