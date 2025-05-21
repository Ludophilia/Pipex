/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:58:23 by jgermany          #+#    #+#             */
/*   Updated: 2025/05/21 19:53:52 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	psrb_init_progs(int *argc, char ***argv, t_pgb *prgs)
{
	ft_bzero(prgs, (*argc + 1) * sizeof(t_pgb));
	if (ft_strncmp(**argv, "here_doc", 9) != 0)
		return (0);
	if (((*argc)--, ++(*argv)) && access(HRDC_NAME, F_OK) == 0)
		unlink(HRDC_NAME);
	prgs[0].in_ty = CHTB_HERE;
	prgs[*argc - 2 - 1].out_ty = CHTB_APPN;
	return (0);
}

static int	psrb_set_prog_in(int prg_id, char **argv, t_pgb *prgs)
{
	if (prg_id == 0)
	{
		prgs[0].in[1] = -1;
		if (prgs[0].in_ty == CHTB_HERE)
			prgs[0].in[0] = hrm_open_heredoc(*argv);
		else 
			prgs[0].in[0] = fmgb_open(argv[0], O_RDONLY, 0);
		if (prgs[0].in[0] == -1)
			return (-1);
	}
	else
	{
		prgs[prg_id].in[0] = prgs[prg_id - 1].out[0];
		prgs[prg_id].in[1] = prgs[prg_id - 1].out[1];
		prgs[prg_id].in_ty = prgs[prg_id - 1].out_ty;
	}
	return (0);
}

static int	psrb_set_prog_out(int prg_id, int argc, char **argv, t_pgb *prgs)
{
	int	rdr_fl;

	rdr_fl = FL_FLGS;
	if (prg_id == (argc - 2) - 1)
	{
		if (prgs[prg_id].out_ty == CHTB_APPN)
			rdr_fl = APN_FLGS;
		prgs[prg_id].out[0] = -1;
		prgs[prg_id].out[1] = fmgb_open(argv[argc - 1], rdr_fl, FL_PRMS);
		if (prgs[prg_id].out[1] == -1)
			return (-1);
	}
	else
	{
		if (fmgb_pipe(prgs[prg_id].out) == -1)
			return (-1);
	}
	return (0);
}

int	psrb_parse_progs(int argc, char **argv, t_pgb *prgs)
{
	int	prg_id;

	prg_id = -1;
	psrb_init_progs(&argc, &argv, prgs);
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
