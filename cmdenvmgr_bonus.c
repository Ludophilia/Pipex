/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdenvmgr_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:58:23 by jgermany          #+#    #+#             */
/*   Updated: 2023/06/12 22:46:59 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdenvmgr_bonus.h"

static int	get_user_input(char **argv, int *limiter_match, int infd)
{
	char	*buffer;

	if (write(1, "> ", 2) == -1 || limiter_match == NULL || infd < 0)
		return (-1);
	buffer = get_next_line(0);
	if (buffer == NULL)
		return (-1);
	*limiter_match = ft_strncmp(buffer, argv[2], ft_strlen(argv[2])) == 0;
	if (*limiter_match)
	{
		free(buffer);
		return (0);
	}
	if (write(infd, buffer, ft_strlen(buffer)) == -1)
	{
		free(buffer);
		return (-1);
	}
	free(buffer);
	return (0);
}

static int	process_input_file(char **argv)
{
	int		infd;
	int		limiter_match;

	if (ft_strncmp("here_doc", argv[1], 9) == 0)
	{
		limiter_match = 0;
		infd = check_and_open("tmp", O_CREAT | O_RDWR, NFILE_PERMS);
		if (infd == -1)
			return (-1);
		while (limiter_match != 1)
		{
			if (get_user_input(argv, &limiter_match, infd) == -1)
			{
				unlink("tmp");
				return (-1);
			}
		}
		return (infd);
	}
	infd = check_and_open(argv[1], O_RDONLY, 0);
	if (infd == -1)
		return (-1);
	return (infd);
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
	}
	else
	{
		cmdenvs[head].in[0] = cmdenvs[head - 1].out[0];
		cmdenvs[head].in[1] = cmdenvs[head - 1].out[1];
	}
	return (0);
}

// When the first parameter (argv[1]) is here_doc, openflags of check_and_open
// should be affected...
static int	set_cmdenv_out(t_cmd *cmdenvs, int head, int argc, char **argv)
{
	if ((head + 1) == (argc - 3)) // Affected by the here doc...
	{
		cmdenvs[head].out[0] = -1;
		cmdenvs[head].out[1] = check_and_open(argv[argc - 1],
				O_CREAT | O_WRONLY, NFILE_PERMS);
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
	while (++head < (argc - 3)) // Affected by the here doc...
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
