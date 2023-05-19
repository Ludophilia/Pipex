/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdmgr.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:39:27 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/19 19:30:54 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDMGR_H

# define CMDMGR_H

# include <stdlib.h>
# include <sys/wait.h>

# include "commonlibs.h"
# include "sanicheck.h"

int	redir_and_exec(char **args, char **envp);

#endif