/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:45:09 by jgermany          #+#    #+#             */
/*   Updated: 2025/04/25 19:28:29 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// 22/04 = Again, let's make that clearer and even more compact

// - [ ] Do not forget to rename files and add the prefix so those functions 
// are easily
int	main(int argc, char **argv, char **envp)
{	
	t_prg	prgs[2 + 1];

	if ((++argv, --argc, argc != 4) && ft_eprintf(ERR_USAGE, strerror(EINVAL)))
		return (1);
	if (cmpsr_parse_progs(argc, argv, prgs) == -1)
		return (2);
	// 26/04 - Please compile that and test it in valgrind with fds and stuff
	ft_printf("infd 0 -> %i\n", prgs[0].in_fds[0]);
	ft_printf("cmd 0 -> %s\n", prgs[0].cmd);
	ft_printf("cmd 1 -> %s\n", prgs[1].cmd);
	ft_printf("outfd 1 -> %i\n", prgs[1].out_fds[1]);
	ft_printf("cmd 2 -> %s\n", prgs[2].cmd);
	fmgr_close(0, DIR_FWD, prgs);
	(void)envp;
	// if (fork_and_exec(cmdenvs, envp) == -1)
	// 	return (3);
	return (0);
}
