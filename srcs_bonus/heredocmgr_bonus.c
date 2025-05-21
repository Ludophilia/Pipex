/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocmgr_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:02:02 by jgermany          #+#    #+#             */
/*   Updated: 2025/05/21 19:58:06 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	hrm_get_user_input(char *limiter, int *off_limit)
{
	char	*usr_in;
	int		lim_len;
	int		hdc_fd;

	hdc_fd = fmgb_open(HRDC_NAME, APN_FLGS, FL_PRMS);
	if (hdc_fd == -1)
		return (-1);
	usr_in = get_next_line(0);
	if (usr_in == NULL)
		return (-1);
	lim_len = ft_strlen(limiter);
	if (ft_strncmp(usr_in, limiter, lim_len) == 0 && usr_in[lim_len] == '\n')
	{
		(free(usr_in), (*off_limit)--);
		return (close(hdc_fd));
	}
	if (write(hdc_fd, usr_in, ft_strlen(usr_in)) == -1)
	{
		(free(usr_in), close(hdc_fd));
		return (-1);
	}
	free(usr_in);
	return (close(hdc_fd));
}

int	hrm_open_heredoc(char *limiter)
{
	int	off_limit;
	int	hdc_fd;

	off_limit = 1;
	while (off_limit)
	{
		if (write(1, "> ", 2) == -1
			|| hrm_get_user_input(limiter, &off_limit) == -1)
			return (-1);
	}
	hdc_fd = fmgb_open(HRDC_NAME, O_RDONLY, 0);
	if (hdc_fd == -1)
		return (-1);
	return (hdc_fd);
}
