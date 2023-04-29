/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checkers_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 23:04:11 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/02 21:46:03 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"

bool	is_valid_flg(char c)
{
	if (c == ' ' || c == '+' || c == '#' || c == '-' || c == '0')
		return (1);
	return (0);
}

bool	is_valid_type(char c)
{
	if (c == 'c' || c == '%' || c == 's' || c == 'd' || c == 'i'
		|| c == 'u' || c == 'x' || c == 'X' || c == 'p')
		return (1);
	return (0);
}
