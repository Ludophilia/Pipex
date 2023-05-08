/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 13:53:57 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/08 17:10:08 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTER_H

# define PRINTER_H

# include "../commons/commons.h"

void	print_char(char c, t_meta *meta);
void	print_str(char *str, t_meta *meta);
void	print_nbr(t_nbr nb, char *base, t_flag *flags, t_meta *meta);

#endif