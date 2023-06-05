/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:45:09 by jgermany          #+#    #+#             */
/*   Updated: 2023/06/05 14:58:56 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	set_cmdenv_in(t_cmd *cmdenvs, int head, char **argv)
{
	if (head == 0)
	{
		cmdenvs[head].in[0] = check_and_open(argv[1], R_OK, O_RDONLY);
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

int	set_cmdenv_out(t_cmd *cmdenvs, int head, int argc, char **argv)
{
	if ((head + 1) == (argc - 3))
	{
		cmdenvs[head].out[0] = -1;
		cmdenvs[head].out[1] = check_and_open(argv[argc - 1], W_OK, O_WRONLY);
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

int	build_cmdenvs(t_cmd *cmdenvs, int argc, char **argv)
{
	int		head;

	head = -1;
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

int	main(int argc, char **argv, char **envp)
{	
	t_cmd	cmdenvs[1024];

	if (check_argc(argc) == -1) // Should check argc == 5 or higher...
		return (1);
	if (build_cmdenvs(cmdenvs, argc, argv) == -1)
		return (1);
	if (fork_and_exec(cmdenvs, envp) == -1)
		return (1);
	return (0);
}
