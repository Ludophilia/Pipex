/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocmgr_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:02:07 by jgermany          #+#    #+#             */
/*   Updated: 2023/06/13 19:39:16 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOCMGR_BONUS_H

# define HEREDOCMGR_BONUS_H
# define NFILE_PERMS 00664

# include "filemgr_bonus.h"
# include "commonlibs_bonus.h"

void	update_for_heredoc(int *limit, int *offset, int *flags);
int		process_input_file(char **argv);

#endif