/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filemgr_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 22:58:16 by jgermany          #+#    #+#             */
/*   Updated: 2025/05/16 20:20:42 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	fmgb_open(char *path, int openflags, mode_t openmode)
{
	int	fd;

	if (path == NULL)
		return (-1);
	fd = open(path, openflags, openmode);
	if (fd == -1 && ft_eprintf(ERR_PTH, path, strerror(errno)))
		return (-1);
	return (fd);
}

int	fmgb_pipe(int fds[2])
{
	if (pipe(fds) == -1 && ft_eprintf(ERR_GNR, strerror(errno)))
		return (-1);
	return (0);
}

int	fmgb_access(char *path, int type)
{
	if (access(path, type) == -1)
	{
		ft_eprintf(ERR_PTH, path, strerror(errno));
		return (-1);
	}
	return (0);
}

int	fmgb_close(int *prg_fds, int end)
{
	if (prg_fds[end] <= 2)
		return (0);
	if (close(prg_fds[end]) == -1 && ft_eprintf(ERR_GNR, strerror(errno)))
		return (-1);
	prg_fds[end] = -1;
	return (0);
}

int	fmgb_closeall(int from_id, int reverse, t_prg *prgs)
{
	t_prg	prg;

	while ((reverse && from_id >= 0) || (!reverse && prgs[from_id].cmd))
	{
		prg = prgs[from_id];
		if ((from_id == 0 && fmgb_close(prg.in, 0) == -1)
			|| fmgb_close(prg.out, 0) == -1
			|| fmgb_close(prg.out, 1) == -1)
			return (-1);
		if (reverse)
			from_id--;
		else
			++from_id;
	}
	return (1);
}
