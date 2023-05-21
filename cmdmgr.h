/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdmgr.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:39:27 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/21 12:43:37 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDMGR_H

# define CMDMGR_H

# include <stdlib.h>
# include <sys/wait.h>

# include "commonlibs.h"
# include "sanicheck.h"
# include "filemgr.h"

# define DEFAULT_PATH "/bin:/usr/bin"

int	fork_and_exec(char *cmd, int infd, int outfd, char **envp);

#endif