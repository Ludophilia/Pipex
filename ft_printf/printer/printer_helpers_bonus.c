/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_helpers_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 20:19:32 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/15 19:47:17 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printer_bonus.h"

static void	print_nbr_sign(t_nbr nb, t_flag *flags, int *count)
{
	if (!(nb.sign || flags->plus_f || flags->space_f))
		return ;
	if (nb.sign)
		putchar_cc('-', count);
	else
	{
		if (flags->plus_f)
			putchar_cc('+', count);
		else if (flags->space_f)
			putchar_cc(' ', count);
	}
}

static void	print_hex_prefix(t_flag *flags, int *count)
{
	if (!(flags->pound_f || is_ptr(flags)))
		return ;
	if (is_hex(flags, 1, 0) || is_ptr(flags))
		putstr_cc("0x", count);
	else if (is_hex(flags, 0, 1))
		putstr_cc("0X", count);
}

void	print_prefix(t_nbr nb, t_flag *flags, int *count)
{
	if (is_int(flags))
		print_nbr_sign(nb, flags, count);
	else if ((is_hex(flags, 1, 1) || is_ptr(flags)) && nb.abs != 0 && !nb.sign)
		print_hex_prefix(flags, count);
}

void	print_filler(t_flag *flags, bool zfill, int *count)
{
	while (flags->field_v-- > 0)
		putchar_cc((char [2]){' ', '0'}[zfill], count);
}

void	print_nbr_filler(t_nbr nb, t_flag *flags, bool before, int *count)
{
	if (before)
	{
		if (!flags->zero_f || (flags->zero_f && (flags->prec_f
					|| (!nb.abs && is_ptr(flags)))))
			print_filler(flags, false, count);
		else if (flags->zero_f && !flags->prec_f)
			print_filler(flags, true, count);
		return ;
	}
	print_filler(flags, false, count);
}
