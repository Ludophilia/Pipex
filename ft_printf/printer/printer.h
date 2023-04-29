/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 13:53:57 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/04 13:59:48 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTER_H

# define PRINTER_H

# include "../commons/commons.h"

void	print_char(char c, int *count);
void	print_str(char *str, int *count);
void	print_nbr(t_nbr nb, char *base, t_flag *flags, int *count);

#endif