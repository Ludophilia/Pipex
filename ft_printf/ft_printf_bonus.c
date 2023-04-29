/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:28:28 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/04 17:07:39 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	process_format(const char *format, va_list *args, int *count)
{
	int		i;
	int		offset;

	i = -1;
	while (format[++i])
	{
		if (format[i] == '%')
		{
			offset = proc_specif((char *)format + i + 1, args, count);
			if (offset == -1)
				return (-1);
			else
				i += offset;
		}
		else
			putchar_cc(format[i], count);
	}
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int		count;
	va_list	args;

	if (!format)
	{
		errno = EINVAL;
		return (-1);
	}
	count = 0;
	va_start(args, format);
	if (process_format(format, &args, &count) == -1)
		return (-1);
	va_end(args);
	return (count);
}
