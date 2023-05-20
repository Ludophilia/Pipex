/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filemgr.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 22:58:37 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/20 18:56:05 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEMGR_H

# define FILEMGR_H
# define DEFAULT_PATH "/bin:/usr/bin"

# include "sanicheck.h"

int		check_and_open(char *path, int accessmode, int openmode);
char	**get_paths(char **envp);
char	*search_executable(char *cmd, char **envp);

#endif