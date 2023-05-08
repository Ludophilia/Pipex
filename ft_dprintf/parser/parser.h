/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:13:27 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/08 17:09:29 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# define PARSER_H

# include <stdint.h>

# include "../commons/commons.h"
# include "../printer/printer.h"

int	proc_specif(char *spec, va_list *args, t_meta *meta);

#endif
