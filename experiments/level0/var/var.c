/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:03:57 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/28 13:30:55 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>

void	print_nbs(int nb, ...)
{
	va_list	args;

	va_start(args, nb);
	printf("%i ", nb);
	nb = va_arg(args, int);
	while (nb)
	{
		printf("%i ", nb);
		nb = va_arg(args, int);
	}
	va_end(args);
}

int	main(void)
{
	print_nbs(1, 2, 3, 4, 5, 0); // 0 mark the end of the array...
}