/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocmgr_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:02:02 by jgermany          #+#    #+#             */
/*   Updated: 2025/05/18 20:54:10 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_tmpfile(char *filename, char **argv)
{
	if (ft_strncmp("here_doc", argv[1], 9) == 0 && access(filename, F_OK) == 0)
		unlink(filename);
}

void	update_for_heredoc(int *limit, int *offset, int *flags)
{
	if (limit != NULL)
		*limit -= 1;
	if (offset != NULL)
		*offset += 1;
	if (flags != NULL)
		*flags = O_APPEND | O_CREAT | O_WRONLY;
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
	infd = fmgb_open(*filename, O_CREAT | O_RDWR, FL_PRMS);
	if (infd == -1)
		return (-1);
	while (limiter_match != 1)
	{
		if (get_user_input(argv, &limiter_match, infd) == -1)
		{
			close(infd);
			return (-1);
		}
	}
	close(infd);
	return (0);
}

// 19/05/25 
int	hrm_open_heredoc(char **argv) // *argv -> LIMITER
{
	int		infd;
	char	*filename;

	filename = argv[1];
		if (process_user_input(argv, &filename) == -1)
			return (-1);
	infd = fmgb_open(filename, O_RDONLY, 0);
	if (infd == -1)
		return (-1);
	return (infd);
}
