/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanicheck.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:47:30 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/11 22:34:24 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SANITIZER_H

# define SANITIZER_H

# include <errno.h>
# include <stdio.h>
# include <unistd.h> // duplicate ?
# include "ft_dprintf/ft_dprintf.h" // duplicate ?

int		check_perm(char *filename, int mode);
int		check_argc(int argc);
int		check_args(int argc, char **argv);

#endif