/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocmgr_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:02:02 by jgermany          #+#    #+#             */
/*   Updated: 2023/06/13 20:24:35 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredocmgr_bonus.h"

void	update_for_heredoc(int *limit, int *offset, int *flags)
{
	if (limit != NULL)
		*limit -= 1;
	if (offset != NULL)
		*offset += 1;
	if (flags != NULL)
	{
		*flags |= O_APPEND;
		*flags &= O_CREAT | 0xFF;
	}
}

static int	get_user_input(char **argv, int *limiter_match, int infd)
{
	char	*buffer;
	char	*limiter;

	if (write(1, "> ", 2) == -1 || limiter_match == NULL || infd < 0)
		return (-1);
	buffer = get_next_line(0);
	limiter = ft_strjoin(argv[2], "\n");
	if (buffer == NULL || limiter == NULL)
		return (-1);
	*limiter_match = ft_strncmp(buffer, limiter, ft_strlen(limiter)) == 0;
	free(limiter);
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

static int	process_user_input(char **argv, char **filename)
{
	int	limiter_match;
	int	infd;

	if (filename == NULL)
		return (-1);
	limiter_match = 0;
	*filename = "tmp";
	infd = check_and_open(*filename, O_CREAT | O_RDWR, NFILE_PERMS);
	if (infd == -1)
		return (-1);
	while (limiter_match != 1)
	{
		if (get_user_input(argv, &limiter_match, infd) == -1)
		{
			unlink(*filename);
			close(infd);
			return (-1);
		}
	}
	close(infd);
	return (0);
}

int	process_input_file(char **argv)
{
	int		infd;
	char	*filename;

	filename = argv[1];
	if (ft_strncmp("here_doc", argv[1], 9) == 0)
		if (process_user_input(argv, &filename) == -1)
			return (-1);
	infd = check_and_open(filename, O_RDONLY, 0);
	if (infd == -1)
		return (-1);
	return (infd);
}
