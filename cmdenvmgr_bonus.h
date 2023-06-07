/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdenvmgr_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:17:46 by jgermany          #+#    #+#             */
/*   Updated: 2023/06/07 21:45:30 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDENVMGR_H

# define CMDENVMGR_H
# define NFILE_PERMS 00664

# include "filemgr.h"
# include "commonlibs.h"

int	build_cmdenvs(t_cmd *cmdenvs, int argc, char **argv);

#endif