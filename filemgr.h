/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filemgr.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 22:58:37 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/13 12:29:01 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEMGR_H

# define FILEMGR_H

# include <fcntl.h>

int	get_fd(char *path, int mode);

#endif