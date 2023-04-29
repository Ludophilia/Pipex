/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commons.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:34:45 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/29 14:01:44 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMONS_H

# define COMMONS_H

# include <stdarg.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>

# include "../../libft/libft.h"

# define B10 "0123456789"
# define B16U "0123456789ABCDEF"
# define B16L "0123456789abcdef"

typedef struct s_nbr
{
	bool			sign: 1;
	unsigned long	abs;
}	t_nbr;

typedef struct s_flag
{
	unsigned char	conv_t: 7;
}	t_flag;

void	putchar_cc(char c, int *count);
void	putstr_cc(char *s, int *count);

#endif