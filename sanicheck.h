/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanicheck.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:47:30 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/22 11:22:03 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SANICHECK_H

# define SANICHECK_H

# include <errno.h>

# include "commonlibs.h"

int		ft_perror(char *message, int statuscode);
int		check_argc(int argc);
int		check_perm(char *filename, int mode);
void	free_strs(char **strs, int offset);

#endif