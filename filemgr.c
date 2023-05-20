/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filemgr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 22:58:16 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/20 12:19:37 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filemgr.h"

int	check_and_open(char *path, int accessmode, int openmode)
{
	int	fd;

	if (check_perm(path, accessmode) == -1)
		return (-1);
	fd = open(path, openmode);
	if (fd == -1)
		return (-1);
	return (fd);
}
