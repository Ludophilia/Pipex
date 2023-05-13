/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdmgr.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:39:27 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/13 12:28:10 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDMGR_H

# define CMDMGR_H

# include <unistd.h> // duplicate ?
# include <stdlib.h> // duplicate ?
# include <stdio.h> // duplicate ?
# include <sys/wait.h>

# include "libft/libft.h" // duplicate ?

int	exec_cmd(char *cmd, int fd);

#endif