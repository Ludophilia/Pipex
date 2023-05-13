/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filemgr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 22:58:16 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/13 12:05:51 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filemgr.h"

int	get_fd(char *path, int mode)
{
	int	fd;

	fd = open(path, mode);
	if (fd == -1)
		return (-1);
	return (0);
}
