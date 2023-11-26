/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdenvmgr_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:17:46 by jgermany          #+#    #+#             */
/*   Updated: 2023/06/13 17:12:43 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDENVMGR_BONUS_H

# define CMDENVMGR_BONUS_H
# define NFILE_PERMS 00664

# include "heredocmgr_bonus.h"
# include "filemgr_bonus.h"
# include "commonlibs_bonus.h"

int	build_cmdenvs(t_cmd *cmdenvs, int argc, char **argv);

#endif