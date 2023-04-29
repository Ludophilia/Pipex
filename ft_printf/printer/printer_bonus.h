/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 13:53:57 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/04 17:49:28 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTER_BONUS_H

# define PRINTER_BONUS_H

# include "../commons/commons_bonus.h"
# include "../writer/writer_bonus.h"

bool	is_int(t_flag *flags);
bool	is_hex(t_flag *flags, bool lowercase, bool uppercase);
bool	is_ptr(t_flag *flags);
bool	is_str(t_flag *flags);
bool	is_chr(t_flag *flags, bool is_percent);

void	print_prefix(t_nbr nb, t_flag *flags, int *count);
void	print_filler(t_flag *flags, bool zfill, int *count);
void	print_nbr_filler(t_nbr nb, t_flag *flags, bool before, int *count);

void	print_char(char c, t_flag *flags, int *count);
void	print_str(char *str, t_flag *flags, int *count);
void	print_nbr(t_nbr nb, char *base, t_flag *flags, int *count);

#endif