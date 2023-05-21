/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commonlibs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:34:34 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/21 16:55:36 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMONLIBS_H

# define COMMONLIBS_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

# include "libft/libft.h"
# include "ft_dprintf/ft_dprintf.h"

typedef struct s_cmd
{
	char 	*cmd;
	int		infd;
	int		outfd;
}	t_cmd;

#endif