/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanicheck.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:47:30 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/13 16:08:06 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SANICHECK_H

# define SANICHECK_H

# include <errno.h>

# include "commonlibs.h"

int		check_argc(int argc);
int		check_perm(char *filename, int mode);
int		check_args(int argc, char **argv);

#endif