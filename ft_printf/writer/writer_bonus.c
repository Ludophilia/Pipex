/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:18:20 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/02 22:56:11 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "writer_bonus.h"

void	write_char(char c, t_list **head)
{
	t_list	*curr_node;
	t_list	*new_node;
	size_t	len;

	curr_node = ft_lstlast(*head);
	len = ft_strlen((char *)(curr_node->content));
	if (len == BUFFER_SIZE)
	{
		new_node = init_node(c);
		if (!new_node)
		{
			errno = ENOMEM;
			return ;
		}
		ft_lstadd_back(head, new_node);
	}
	else
		((char *)(curr_node->content))[len] = c;
}

void	write_str(char *s, t_list **head)
{
	int	i;

	i = -1;
	while (s[++i])
		write_char(s[i], head);
}

void	write_precision(t_flag *flags, t_list **head)
{
	t_list	*prec_node;

	prec_node = init_node(0);
	if (!prec_node)
	{
		errno = ENOMEM;
		return ;
	}
	flags->prec_v -= cont_len(head);
	while (flags->prec_v-- > 0)
		write_char('0', &prec_node);
	ft_lstlast(prec_node)->next = *head;
	*head = prec_node;
}

void	write_abs_base(t_nbr nb, char *base, t_flag *flags,
t_list **head)
{
	unsigned long	radix;

	if (!nb.abs && flags->prec_f && !flags->prec_v)
		return ;
	radix = ft_strlen(base);
	if (nb.abs >= radix)
		write_abs_base((t_nbr){nb.sign, nb.abs / radix}, base, flags, head);
	write_char(base[nb.abs % radix], head);
}

void	write_nbr_base(t_nbr nb, char *base, t_flag *flags,
t_list **head)
{
	if (nb.abs == 0 && flags->conv_t == 'p')
		write_str("(nil)", head);
	else
		write_abs_base(nb, base, flags, head);
}
