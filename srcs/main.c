/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:45:09 by jgermany          #+#    #+#             */
/*   Updated: 2025/04/26 19:30:34 by jegerman         ###   ########.fr       */
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

	(void)envp;

	// 27/04 - Next up
	// if (fork_and_exec(cmdenvs, envp) == -1)
	// 	return (3);

	fmgr_close(0, DIR_FWD, prgs); // Will I ever need this?
	return (0);
}

// ft_printf("(cmd0 -> \"%s\")\n", prgs[0].cmd);
// ft_printf("cmd0.in_fds[0] -> %i\n", prgs[0].in_fds[0]);
// ft_printf("cmd0.in_fds[1] -> %i\n", prgs[0].in_fds[1]);
// ft_printf("cmd0.out_fds[0] -> %i\n", prgs[0].out_fds[0]);
// ft_printf("cmd0.out_fds[1] -> %i\n", prgs[0].out_fds[1]);

// ft_printf("\n(cmd1 -> \"%s\")\n", prgs[1].cmd);
// ft_printf("cmd1.in_fds[0] -> %i\n", prgs[1].in_fds[0]);
// ft_printf("cmd1.in_fds[1] -> %i\n", prgs[1].in_fds[1]);
// ft_printf("cmd1.out_fds[0] -> %i\n", prgs[1].out_fds[0]);
// ft_printf("cmd1.out_fds[1] -> %i\n\n", prgs[1].out_fds[1]);

// ft_printf("\n(cmd2 -> \"%s\")\n", prgs[2].cmd);