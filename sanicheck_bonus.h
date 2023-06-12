/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanicheck_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:47:30 by jgermany          #+#    #+#             */
/*   Updated: 2023/06/12 22:44:04 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SANICHECK_BONUS_H

# define SANICHECK_BONUS_H

# include <errno.h>
# include <stdio.h>
# include <string.h>

# include "commonlibs_bonus.h"

int		ft_perror(int statuscode, char *message);
int		check_argc(int argc);
int		check_perm(char *filename, int mode);
void	free_strs(char **strs, int offset);

#endif
