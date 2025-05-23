/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:01:54 by jegerman          #+#    #+#             */
/*   Updated: 2025/05/16 16:18:49 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_bonus.h"

int	ft_lstsize(t_list *lst)
{
	size_t	size;

	if (lst == NULL)
		return (0);
	size = 0;
	while (lst && ++size)
		lst = lst->next;
	return (size);
}
