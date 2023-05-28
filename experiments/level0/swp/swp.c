/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:31:34 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/28 17:39:51 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	swaparr(int *tab1, int *tab2)
{
	int	tmp[2];

	tmp[0] = tab1[0];
	tmp[1] = tab1[1];
	tab1[0] = tab2[0];
	tab1[1] = tab2[1];
	tab2[0] = tmp[0];
	tab2[1] = tmp[1];
}

void	printarr(int *tab1, int *tab2)
{
	printf("tab1[0] = %i ; tab1[1] = %i\n", tab1[0], tab1[1]);
	printf("tab2[0] = %i ; tab2[1] = %i\n\n", tab2[0], tab2[1]);
}

int	main() {
	int	tab1[2] = {0, 1};
	int	tab2[2] = {1, 0};

	printarr(tab1, tab2);
	swaparr(tab1, tab2);
	printarr(tab1, tab2);
	return (0);
}