/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdmgr_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:39:27 by jgermany          #+#    #+#             */
/*   Updated: 2023/06/07 22:15:36 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDMGR_BONUS_H

# define CMDMGR_BONUS_H

# include <stdlib.h>
# include <sys/wait.h>

# include "filemgr.h"
# include "sanicheck.h"
# include "commonlibs.h"

int	fork_and_exec(t_cmd *cmdenvs, char **envp);

#endif