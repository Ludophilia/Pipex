/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 21:12:12 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/15 18:26:07 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"

int	proc_flags(char *spec, t_flag *flags)
{
	int	i;

	i = 0;
	while (spec[i] && is_valid_flg(spec[i]))
	{
		if (spec[i] == ' ')
			flags->space_f = 1;
		else if (spec[i] == '+')
			flags->plus_f = 1;
		else if (spec[i] == '-')
			flags->dash_f = 1;
		else if (spec[i] == '#')
			flags->pound_f = 1;
		else if (spec[i] == '0')
			flags->zero_f = 1;
		i++;
	}
	return (i);
}

int	proc_options(char *spec, t_flag *flags)
{
	int	i;

	i = 0;
	if (spec[i] && ft_isdigit(spec[i]))
	{
		flags->field_f = 1;
		flags->field_v = ft_atoi(spec + i);
	}
	while (spec[i] && ft_isdigit(spec[i]))
		i++;
	if (spec[i] == '.')
	{
		flags->prec_f = 1;
		i++;
	}
	if (spec[i] && ft_isdigit(spec[i]))
		flags->prec_v = ft_atoi(spec + i);
	while (spec[i] && ft_isdigit(spec[i]))
		i++;
	return (i);
}

int	proc_conv(char *spec, va_list *args, t_flag *flags, int *count)
{
	if (!is_valid_type(*spec))
	{
		errno = EINVAL;
		return (0);
	}
	flags->conv_t = *spec;
	if (*spec == 'c' || *spec == '%' || *spec == 's')
		proc_char_conv(spec, args, flags, count);
	else
		proc_nbr_conv(spec, args, flags, count);
	return (1);
}

int	proc_specif(char *spec, va_list *args, int *count)
{
	t_flag	*flags;
	int		i;

	flags = ft_calloc(1, sizeof(t_flag));
	if (!flags)
		return (-1);
	i = proc_flags(spec, flags);
	i += proc_options(spec + i, flags);
	if (!proc_conv(spec + i, args, flags, count))
		return (-1);
	i++;
	free(flags);
	return (i);
}
