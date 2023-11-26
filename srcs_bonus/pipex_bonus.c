/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:45:09 by jgermany          #+#    #+#             */
/*   Updated: 2023/06/14 16:48:07 by jgermany         ###   ########.fr       */
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
