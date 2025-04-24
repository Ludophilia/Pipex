/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdenvmgr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:58:23 by jgermany          #+#    #+#             */
/*   Updated: 2025/04/24 15:26:18 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	set_cmdenv_in(t_cmd *cmdenvs, int head, char **argv)
{
	if (head == 0)
	{
		cmdenvs[head].in[0] = check_and_open(argv[1], O_RDONLY, 0);
		cmdenvs[head].in[1] = -1;
		if (cmdenvs[head].in[0] == -1)
		{
			close_fds(cmdenvs, head, 1);
			return (-1);
		}
	}
	else
	{
		cmdenvs[head].in[0] = cmdenvs[head - 1].out[0];
		cmdenvs[head].in[1] = cmdenvs[head - 1].out[1];
	}
	return (0);
}

static int	set_cmdenv_out(t_cmd *cmdenvs, int head, int argc, char **argv)
{
	if ((head + 1) == (argc - 3))
	{
		cmdenvs[head].out[0] = -1;
		cmdenvs[head].out[1] = check_and_open(argv[argc - 1],
				O_TRUNC | O_CREAT | O_WRONLY, NFILE_PERMS);
		if (cmdenvs[head].out[1] == -1)
		{
			close_fds(cmdenvs, head, 1);
			return (-1);
		}
	}
	else
	{
		if (pipe(cmdenvs[head].out) == -1)
		{
			close_fds(cmdenvs, head, 1);
			return (-1);
		}
	}
	return (0);
}

static void	init_cmdenvs(t_cmd *cmdenvs, int size)
{
	int	head;

	// if (cmdenvs == NULL)
	// 	return ;
	head = -1;
	while (++head < size)
	{
		cmdenvs[head].cmd = NULL; // Why, it will be erased just after
		cmdenvs[head].in[0] = -1;
		cmdenvs[head].in[1] = -1;
		cmdenvs[head].out[0] = -1;
		cmdenvs[head].out[1] = -1;
		cmdenvs[head].pid = -1;
	}
}

// 23/04 - What does this module do?
//		- Faily simple. It initialize the array of cmdenvs, structs supposed to 
// 		represent the prg and its environment.
// 			- First, with default values
//		- Then, the redirections and the pipes are opened right away.

// That also means that the name build_cmdenvs is too vague.
//	- There is initialization for sure
//	- 
int	build_cmdenvs(t_cmd *cmdenvs, int argc, char **argv)
{
	int		head;

	head = -1;
	init_cmdenvs(cmdenvs, (argc - 3) + 1);
	while (++head < (argc - 3))
	{
		cmdenvs[head].cmd = argv[head + 2];
		if (set_cmdenv_in(cmdenvs, head, argv) == -1)
			return (-1);
		if (set_cmdenv_out(cmdenvs, head, argc, argv) == -1)
			return (-1);
	}
	cmdenvs[head].cmd = NULL;
	return (0);
}
