/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:05:44 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/06 01:02:11 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"

void	proc_char_conv(char *spec, va_list *args, t_flag *flags, int *count)
{
	if (*spec == 'c')
		print_char(va_arg(*args, int), flags, count);
	else if (*spec == '%')
		print_char('%', flags, count);
	else if (*spec == 's')
		print_str(va_arg(*args, char *), flags, count);
}

void	proc_nbr_conv(char *spec, va_list *args, t_flag *flags, int *count)
{
	long			snbr;
	unsigned long	unbr;

	snbr = 0;
	unbr = 0;
	if (*spec == 'd' || *spec == 'i')
		snbr = va_arg(*args, int);
	else if (*spec == 'u' || *spec == 'x' || *spec == 'X')
		unbr = va_arg(*args, unsigned int);
	else if (*spec == 'p')
		unbr = va_arg(*args, uintptr_t);
	if (snbr < 0 && (*spec == 'd' || *spec == 'i'))
		print_nbr((t_nbr){1, -snbr}, B10, flags, count);
	else if (snbr >= 0 && (*spec == 'd' || *spec == 'i'))
		print_nbr((t_nbr){0, snbr}, B10, flags, count);
	else if (*spec == 'u')
		print_nbr((t_nbr){0, unbr}, B10, flags, count);
	else if (*spec == 'x')
		print_nbr((t_nbr){0, unbr}, B16L, flags, count);
	else if (*spec == 'X')
		print_nbr((t_nbr){0, unbr}, B16U, flags, count);
	else if (*spec == 'p')
		print_nbr((t_nbr){0, unbr}, B16L, flags, count);
}
