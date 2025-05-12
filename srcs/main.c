/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:45:09 by jgermany          #+#    #+#             */
/*   Updated: 2025/05/12 21:16:15 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Since approx. 22/04
// 12/04 - Let's test this... thoroughly.
int	main(int argc, char **argv, char **envp)
{
	t_prg	prgs[PGRS_NBR];

	if ((++argv, --argc, argc != 4) && ft_eprintf(ERR_USAGE, strerror(EINVAL)))
		return (1);
	if (psr_parse_progs(argc, argv, prgs) == -1)
		return (2);
	if (pgm_exec_progs(prgs, envp) == -1 && fmg_closeall(0, DIR_FWD, prgs))
		return (3);
	if (fmg_closeall(0, DIR_FWD, prgs) == -1) // Will I ever need this?
		return (4);
	return (0);
}

// ft_printf("(cmd0 -> \"%s\")\n", prgs[0].cmd);
// ft_printf("cmd0.in[0] -> %i\n", prgs[0].in[0]);
// ft_printf("cmd0.in[1] -> %i\n", prgs[0].in[1]);
// ft_printf("cmd0.out[0] -> %i\n", prgs[0].out[0]);
// ft_printf("cmd0.out[1] -> %i\n", prgs[0].out[1]);

// ft_printf("\n(cmd1 -> \"%s\")\n", prgs[1].cmd);
// ft_printf("cmd1.in[0] -> %i\n", prgs[1].in[0]);
// ft_printf("cmd1.in[1] -> %i\n", prgs[1].in[1]);
// ft_printf("cmd1.out[0] -> %i\n", prgs[1].out[0]);
// ft_printf("cmd1.out[1] -> %i\n\n", prgs[1].out[1]);

// ft_printf("\n(cmd2 -> \"%s\")\n", prgs[2].cmd);
