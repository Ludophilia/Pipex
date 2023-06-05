/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filemgr.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 22:58:37 by jgermany          #+#    #+#             */
/*   Updated: 2023/06/05 17:37:24 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEMGR_H

# define FILEMGR_H
# define DEFAULT_PATH "/bin:/usr/bin"
# define NFILE_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)

# include "sanicheck.h"

void	close_fds(t_cmd *cmdenvs, int head, int reverse);
int		check_and_open(char *path, int accessmode,
			int openflags, mode_t openmode);
char	**get_paths(char **envp);
char	*search_executable(char *cmd, char **envp);

#endif