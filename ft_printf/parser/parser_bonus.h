/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:13:27 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/04 17:41:45 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_BONUS_H

# define PARSER_BONUS_H

# include <stdint.h>

# include "../commons/commons_bonus.h"
# include "../printer/printer_bonus.h"

bool	is_valid_flg(char c);
bool	is_valid_type(char c);

void	proc_char_conv(char *spec, va_list *args, t_flag *flags, int *count);
void	proc_nbr_conv(char *spec, va_list *args, t_flag *flags, int *count);

int		proc_flags(char *spec, t_flag *flags);
int		proc_options(char *spec, t_flag *flags);
int		proc_conv(char *spec, va_list *args, t_flag *flags, int *count);
int		proc_specif(char *spec, va_list *args, int *count);

#endif
