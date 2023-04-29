/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commons_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:34:45 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/29 14:01:29 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMONS_BONUS_H

# define COMMONS_BONUS_H

# include <stdarg.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>

# include "../../libft/libft.h"

# define BUFFER_SIZE 20

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
	bool			space_f: 1;
	bool			plus_f: 1;
	bool			pound_f: 1;
	bool			dash_f: 1;
	bool			zero_f: 1;
	bool			field_f: 1;
	bool			prec_f: 1;
	int				field_v;
	int				prec_v;
}	t_flag;

void	putchar_cc(char c, int *count);
void	putstr_cc(char *s, int *count);

t_list	*init_node(char c);
size_t	cont_len(t_list **head);
size_t	print_list(t_list **head, int *count);

#endif