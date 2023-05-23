/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commonlibs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:34:34 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/23 14:38:03 by jgermany         ###   ########.fr       */
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

// The first read is ALWAYS from a file. The last write is ALWAYS to a file.
// Try to use void * could be a char * ("/dev/stdin") or int * [3, 5] 
typedef struct s_cmd
{
	char 	*cmd;
	int		*files;
	int		*pipes;
	int		mode; // 0 (in > pipe) 1 (pipe > pipe) 2 (pipe > out)
}	t_cmd;

#endif