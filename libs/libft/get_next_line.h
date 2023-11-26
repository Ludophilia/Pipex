/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:28:31 by jgermany          #+#    #+#             */
/*   Updated: 2023/06/10 18:56:50 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H
# define BUFFER_SIZE 5
# include "libft.h"

int		ft_strchr_sp(const char *s, int c);
char	**free_stash(char **stash);
ssize_t	update_stash(int fd, char **stash);
char	*extract_line(char **stash);

#endif