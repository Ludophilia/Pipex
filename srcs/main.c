/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:45:09 by jgermany          #+#    #+#             */
/*   Updated: 2025/05/13 20:02:12 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	dbg_show_fds(t_prg *prgs, char **envp)
{
	int	i;

	(void)envp;
	i = -1;
	while (prgs[++i].cmd)
	{
		ft_printf("prgs[%i].cmd -> \"%s\"\n", i, prgs[i].cmd);
		ft_printf("\tprgs[%i].in[0] -> %i\n", i, prgs[i].in[0]);
		ft_printf("\tprgs[%i].in[1] -> %i\n", i, prgs[i].in[1]);
		ft_printf("\tprgs[%i].out[0] -> %i\n", i, prgs[i].out[0]);
		ft_printf("\tprgs[%i].out[1] -> %i\n", i, prgs[i].out[1]);
	}
	ft_printf("prgs[%i].cmd -> \"%s\"\n", i, prgs[i].cmd);
}

// 22/04
// 12/04 - Let's test this... thoroughly.
int	main(int argc, char **argv, char **envp)
{
	t_prg	prgs[PGRS_NBR];

	if ((++argv, --argc, argc != 4) && ft_eprintf(ERR_USAGE, strerror(EINVAL)))
		return (1);
	if (psr_parse_progs(argc, argv, prgs) == -1)
		return (2);
		
	(void)dbg_show_fds;
	
	if (pgm_exec_progs(prgs, envp) == -1 && fmg_closeall(0, DIR_FWD, prgs))
		return (3);

	if (fmg_closeall(0, DIR_FWD, prgs) == -1)
		return (4);
	return (0);
}
