/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocmgr_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:02:02 by jgermany          #+#    #+#             */
/*   Updated: 2025/05/20 20:49:47 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	hrm_get_user_input(char *limit, int *off_limit, int hdc_fd)
{
	char	*usr_in;
	int		lim_len;

	if (write(1, HDRC_PRMT, ft_strlen(HDRC_PRMT)) == -1)
		return (-1);
	usr_in = get_next_line(0);
	if (usr_in == NULL)
		return (-1);
	lim_len = ft_strlen(limit);
	if (!ft_strncmp(usr_in, limit, lim_len) && usr_in[lim_len] == '\n')
	{
		(*off_limit)--;
		free(usr_in);
		return (0);
	}
	if (write(hdc_fd, usr_in, ft_strlen(usr_in)) == -1)
	{
		free(usr_in);
		return (-1);
	}
	free(usr_in);
	return (0);
}

int	hrm_open_heredoc(char *limiter)
{
	int	off_limit;
	int	hdc_fd;

	hdc_fd = fmgb_open(HRDC_NAME, HRDC_FLGS, FL_PRMS);
	if (hdc_fd == -1)
		return (-1);
	off_limit = 1;
	while (off_limit)
	{
		if (hrm_get_user_input(limiter, &off_limit, hdc_fd) == -1)
		{
			close(hdc_fd);
			return (-1);
		}
	}
	return (hdc_fd);
}
