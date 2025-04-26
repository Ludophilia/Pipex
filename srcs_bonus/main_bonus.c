/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:45:09 by jgermany          #+#    #+#             */
/*   Updated: 2025/04/26 16:57:31 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	pipex(int argc, char **argv, char **envp)
{
	t_cmd	cmdenvs[1024];

	if (check_args(argc, argv) == -1)
		return (-1);
	if (build_cmdenvs(cmdenvs, argc, argv) == -1)
	{
		close_tmpfile("tmp", argv);
		return (-1);
	}
	if (fork_and_exec(cmdenvs, envp) == -1)
	{
		close_tmpfile("tmp", argv);
		return (-1);
	}
	close_tmpfile("tmp", argv);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	if (pipex(argc, argv, envp) == -1)
		return (1);
	return (0);
}
// // 26/04 - Please compile that and test it in valgrind with fds and stuff

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

// // close(prgs[0].in_fds[0]);
// // close(prgs[1].out_fds[1]);

// ft_printf("cmd2 -> %s\n", prgs[2].cmd);