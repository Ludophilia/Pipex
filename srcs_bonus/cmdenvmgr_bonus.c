/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdenvmgr_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:58:23 by jgermany          #+#    #+#             */
/*   Updated: 2025/04/25 15:46:49 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdenvmgr_bonus.h"

static void	init_cmdenvs(t_cmd *cmdenvs, int size)
{
	int	head;

	if (cmdenvs == NULL)
		return ;
	head = -1;
	while (++head < size)
	{
		cmdenvs[head].cmd = NULL;
		cmdenvs[head].in[0] = -1;
		cmdenvs[head].in[1] = -1;
		cmdenvs[head].out[0] = -1;
		cmdenvs[head].out[1] = -1;
		cmdenvs[head].pid = -1;
	}
}

static int	set_cmdenv_in(t_cmd *cmdenvs, int head, char **argv)
{
	if (head == 0)
	{
		cmdenvs[head].in[0] = process_input_file(argv);
		cmdenvs[head].in[1] = -1;
		if (cmdenvs[head].in[0] == -1)
		{
			close_fds(cmdenvs, head, 1);
			return (-1);
		}
		return (0);
	}
	cmdenvs[head].in[0] = cmdenvs[head - 1].out[0];
	cmdenvs[head].in[1] = cmdenvs[head - 1].out[1];
	return (0);
}

static int	set_cmdenv_out(t_cmd *cmdenvs, int head, int argc, char **argv)
{
	int		limit;
	int		flags;

	limit = argc - 3;
	flags = O_TRUNC | O_CREAT | O_WRONLY;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		update_for_heredoc(&limit, NULL, &flags);
	if ((head + 1) == limit)
	{
		cmdenvs[head].out[0] = -1;
		cmdenvs[head].out[1] = fmgr_open(argv[argc - 1], flags,
				NFILE_PERMS);
		if (cmdenvs[head].out[1] == -1)
		{
			close_fds(cmdenvs, head, 1);
			return (-1);
		}
		return (0);
	}
	if (pipe(cmdenvs[head].out) == -1)
	{
		close_fds(cmdenvs, head, 1);
		return (-1);
	}
	return (0);
}

int	build_cmdenvs(t_cmd *cmdenvs, int argc, char **argv)
{
	int		head;
	int		limit;
	int		offset;

	head = -1;
	limit = argc - 3;
	offset = 2;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		update_for_heredoc(&limit, &offset, NULL);
	init_cmdenvs(cmdenvs, limit + 1);
	while (++head < limit)
	{
		cmdenvs[head].cmd = argv[head + offset];
		if (set_cmdenv_in(cmdenvs, head, argv) == -1)
			return (-1);
		if (set_cmdenv_out(cmdenvs, head, argc, argv) == -1)
			return (-1);
	}
	cmdenvs[head].cmd = NULL;
	return (0);
}
