/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commonlibs_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:34:34 by jgermany          #+#    #+#             */
/*   Updated: 2023/06/07 21:45:39 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMONLIBS_H

# define COMMONLIBS_H

# include <unistd.h>

# include "libft/libft.h"
# include "ft_dprintf/ft_dprintf.h"

typedef struct s_cmd
{
	char	*cmd;
	int		in[2];
	int		out[2];
	pid_t	pid;
}	t_cmd;

#endif