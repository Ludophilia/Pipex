/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filemgr_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 22:58:37 by jgermany          #+#    #+#             */
/*   Updated: 2023/06/07 22:16:29 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEMGR_BONUS_H

# define FILEMGR_BONUS_H
# define DEFAULT_PATH "/bin:/usr/bin"

# include <fcntl.h>

# include "sanicheck.h"
# include "commonlibs.h"

void	close_fds(t_cmd *cmdenvs, int head, int reverse);
int		check_and_open(char *path, int openflags, mode_t openmode);
char	*search_executable(char *cmd, char **envp);

#endif