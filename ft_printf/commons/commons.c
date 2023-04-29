/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:23:44 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/02 23:40:53 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

void	putchar_cc(char c, int *count)
{
	ft_putchar_fd(c, 1);
	*count += 1;
}

void	putstr_cc(char *s, int *count)
{
	ft_putstr_fd(s, 1);
	*count += ft_strlen(s);
}
