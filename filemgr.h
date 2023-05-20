/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filemgr.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 22:58:37 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/20 12:19:11 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEMGR_H

# define FILEMGR_H

# include "sanicheck.h"

int	check_and_open(char *path, int accessmode, int openmode);

#endif