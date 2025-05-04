/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:45:09 by jgermany          #+#    #+#             */
/*   Updated: 2025/05/04 18:53:59 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// 22/04 = Again, let's make that clearer and even more compact

// - [ ] Do not forget to rename files and add the prefix so those functions 
// are easily
int	main(int argc, char **argv, char **envp)
{	
	t_prg	prgs[PGRS_NBR];

	if ((++argv, --argc, argc != 4) && ft_eprintf(ERR_USAGE, strerror(EINVAL)))
		return (1);
	if (cmpsr_parse_progs(argc, argv, prgs) == -1)
		return (2);

	// 5/05
	if (prgmgr_exec_progs(prgs, envp) == -1)
		return (3);

	if (fmgr_close(0, DIR_FWD, prgs) == -1); // Will I ever need this?
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