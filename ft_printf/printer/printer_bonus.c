/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:24:27 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/08 20:10:13 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printer_bonus.h"

static void	set_nbr_field_width(t_nbr nb, t_flag *flags, t_list **head)
{
	flags->field_v -= cont_len(head);
	if (is_int(flags) && (nb.sign || flags->plus_f || flags->space_f))
		flags->field_v -= 1;
	else if (is_hex(flags, 1, 1) && flags->pound_f && nb.abs != 0 && !nb.sign)
		flags->field_v -= 2;
	else if (is_ptr(flags) && nb.abs != 0 && !nb.sign)
		flags->field_v -= 2;
}

void	print_char(char c, t_flag *flags, int *count)
{
	if (flags->field_v && is_chr(flags, 0))
		flags->field_v--;
	if (!flags->dash_f && !is_chr(flags, 1) && flags->field_v != 0)
		print_filler(flags, false, count);
	putchar_cc(c, count);
	if (flags->dash_f && !is_chr(flags, 1) && flags->field_v != 0)
		print_filler(flags, false, count);
}

void	print_str(char *str, t_flag *flags, int *count)
{
	int	i;
	int	pi;

	if (!str && flags->prec_f && flags->prec_v < 6)
		str = "";
	else if (!str)
		str = "(null)";
	i = -1;
	pi = 0;
	if (flags->field_v && is_str(flags) && flags->prec_f)
		while (str[++i] && flags->field_v && i < flags->prec_v)
			flags->field_v--;
	else if (flags->field_v && is_str(flags) && !flags->prec_f)
		while (str[++i] && flags->field_v)
			flags->field_v--;
	if (!flags->dash_f && flags->field_v > 0)
		print_filler(flags, false, count);
	if (flags->prec_f)
		while (str[pi] && pi < flags->prec_v)
			putchar_cc(str[pi++], count);
	if (!flags->prec_f)
		putstr_cc(str, count);
	if (flags->dash_f && flags->field_v > 0)
		print_filler(flags, false, count);
}

void	print_nbr(t_nbr nb, char *base, t_flag *flags, int *count)
{
	t_list	*start_node;

	start_node = init_node(0);
	if (!start_node)
	{
		ft_lstclear(&start_node, free);
		errno = ENOMEM;
		return ;
	}
	write_nbr_base(nb, base, flags, &start_node);
	if (flags->prec_f)
		write_precision(flags, &start_node);
	if (flags->field_f)
		set_nbr_field_width(nb, flags, &start_node);
	if (flags->zero_f && !flags->prec_f && flags->field_f)
		print_prefix(nb, flags, count);
	if (!flags->dash_f && flags->field_v > 0)
		print_nbr_filler(nb, flags, true, count);
	if (!(flags->zero_f && !flags->prec_f && flags->field_f))
		print_prefix(nb, flags, count);
	print_list(&start_node, count);
	if (flags->dash_f && flags->field_v > 0)
		print_nbr_filler(nb, flags, false, count);
	ft_lstclear(&start_node, free);
}
