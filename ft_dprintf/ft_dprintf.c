/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:28:28 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/08 17:31:42 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static int	process_format(const char *format, va_list *args, t_meta *meta)
{
	int		i;
	int		offset;

	i = -1;
	while (format[++i])
	{
		if (format[i] == '%')
		{
			offset = proc_specif((char *)format + i + 1, args, meta);
			if (offset == -1)
				return (-1);
			else
				i += offset;
		}
		else
			print_char(format[i], meta);
	}
	return (0);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	t_meta		meta;
	va_list		args;

	if (!format)
	{
		errno = EINVAL;
		return (-1);
	}
	meta.fd = fd;
	meta.count = 0;
	va_start(args, format);
	if (process_format(format, &args, &meta) == -1)
		return (-1);
	va_end(args);
	return (meta.count);
}
