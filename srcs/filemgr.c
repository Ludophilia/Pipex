/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filemgr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 22:58:16 by jgermany          #+#    #+#             */
/*   Updated: 2025/05/12 20:02:47 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	fmg_open(char *path, int openflags, mode_t openmode)
{
	int	fd;

	if (path == NULL)
		return (-1);
	fd = open(path, openflags, openmode);
	if (fd == -1 && ft_eprintf(ERR_PTH, path, strerror(errno)))
		return (-1);
	return (fd);
}

int	fmg_pipe(int fds[2])
{
	if (pipe(fds) == -1 && ft_eprintf(ERR_GNR, strerror(errno)))
		return (-1);
	return (0);
}

int	fmg_access(char *path, int type)
{
	if (access(path, X_OK) == -1)
	{
		ft_eprintf(ERR_PTH, path, strerror(errno));
		return (-1);
	}
	return (0);
}

int	fmg_close(int *prg_fds, int end)
{
	if (prg_fds[end] == -1)
		return (0);
	if (close(prg_fds[end]) == -1 && ft_eprintf(ERR_GNR, strerror(errno)))
		return (-1);
	prg_fds[end] = -1;
	return (0);
}

int	fmg_closeall(int from, int reverse, t_prg *prgs)
{
	t_prg	prg;
	
	while ((reverse && from >= 0) || (!reverse && prgs[from].cmd))
	{
		prg = prgs[from];
		if ((from == 0 && fmg_close(prg.in, 0) == -1)
			|| fmg_close(prg.out, 0) == -1
			|| fmg_close(prg.out, 1) == -1)
			return (-1);
		if (reverse)
			from--;
		else
			++from;
	}
	return (0);
}
