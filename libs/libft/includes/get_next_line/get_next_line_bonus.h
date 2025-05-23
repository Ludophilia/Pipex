/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:04:27 by jegerman          #+#    #+#             */
/*   Updated: 2025/05/03 15:38:00 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H

# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft_bonus.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

char		*get_next_line(int fd);

#endif