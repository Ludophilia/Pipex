/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filemgr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 22:58:16 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/11 23:21:19 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filemgr.h"

int		get_fd(char *path, int mode)
{
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (1);
}
