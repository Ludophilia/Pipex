/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:58:23 by jgermany          #+#    #+#             */
/*   Updated: 2025/05/18 18:51:32 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	psr_set_prog_in(int prg_id, char **argv, t_prg *prgs)
{
	if (prg_id == 0)
	{
		prgs[prg_id].in[1] = -1;
		prgs[prg_id].in[0] = fmg_open(argv[prg_id], O_RDONLY, 0);
		if (prgs[prg_id].in[0] == -1)
			return (-1);
	}
	else
	{
		prgs[prg_id].in[0] = prgs[prg_id - 1].out[0];
		prgs[prg_id].in[1] = prgs[prg_id - 1].out[1];
	}
	return (0);
}

static int	psr_set_prog_out(int prg_id, int argc, char **argv, t_prg *prgs)
{
	if (prg_id == (argc - 2) - 1)
	{
		prgs[prg_id].out[0] = -1;
		prgs[prg_id].out[1] = fmg_open(argv[argc - 1], FL_FLGS, FL_PRMS);
		if (prgs[prg_id].out[1] == -1)
			return (-1);
	}
	else
	{
		if (fmg_pipe(prgs[prg_id].out) == -1)
			return (-1);
	}
	return (0);
}

int	psr_parse_progs(int argc, char **argv, t_prg *prgs)
{
	int	prg_id;

	prg_id = -1;
	ft_memset(prgs, 0, PGRS_NBR * sizeof(t_prg));
	while (++prg_id < (argc - 2))
	{
		prgs[prg_id].cmd = argv[1 + prg_id];
		if (psr_set_prog_in(prg_id, argv, prgs) == -1
			|| psr_set_prog_out(prg_id, argc, argv, prgs) == -1)
		{
			fmg_closeall(prg_id, DIR_REV, prgs);
			return (-1);
		}
	}
	prgs[prg_id].cmd = NULL;
	return (0);
}
