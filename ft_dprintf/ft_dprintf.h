/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:49:43 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/08 17:29:07 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H

# define FT_DPRINTF_H

# include "commons/commons.h"
# include "printer/printer.h"
# include "parser/parser.h"

int	ft_dprintf(int fd, const char *format, ...);

#endif