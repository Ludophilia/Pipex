/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_checkers_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 22:35:39 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/04 17:39:52 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printer_bonus.h"

bool	is_int(t_flag *flags)
{
	return (flags->conv_t == 'd' || flags->conv_t == 'i');
}

bool	is_hex(t_flag *flags, bool lowercase, bool uppercase)
{
	if (lowercase && !uppercase)
		return (flags->conv_t == 'x');
	else if (!lowercase && uppercase)
		return (flags->conv_t == 'X');
	return (flags->conv_t == 'x' || flags->conv_t == 'X');
}

bool	is_ptr(t_flag *flags)
{
	return (flags->conv_t == 'p');
}

bool	is_str(t_flag *flags)
{
	return (flags->conv_t == 's');
}

bool	is_chr(t_flag *flags, bool is_percent)
{
	if (is_percent)
		return (flags->conv_t == '%');
	return (flags->conv_t == 'c');
}
