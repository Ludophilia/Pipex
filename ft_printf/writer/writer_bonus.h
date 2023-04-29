/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:14:35 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/04 17:43:02 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRITER_BONUS_H

# define WRITER_BONUS_H

# include "../commons/commons_bonus.h"

void	write_char(char c, t_list **head);
void	write_str(char *s, t_list **head);
void	write_precision(t_flag *flags, t_list **head);
void	write_abs_base(t_nbr nb, char *base, t_flag *flags, t_list **head);
void	write_nbr_base(t_nbr nb, char *base, t_flag *flags, t_list **head);

#endif