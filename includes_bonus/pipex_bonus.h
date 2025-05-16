/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:53:26 by jgermany          #+#    #+#             */
/*   Updated: 2025/05/16 20:29:08 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H

# define PIPEX_BONUS_H

# include "../includes/pipex.h"

# define PGRB_NBR (1024 + 1)

# define USGB_SUGG "usage: pipex <file1> <cmd1> ... <cmdn> <file2>\n"

# define ERRB_USAGE (ERR_GNR USGB_SUGG)

int		psrb_parse_progs(int argc, char **argv, t_prg *prgs);

int		fmgb_open(char *path, int openflags, mode_t openmode);
int		fmgb_close(int *prg_fds, int end);
int		fmgb_pipe(int fds[2]);
int		fmgb_access(char *path, int type);
int		fmgb_closeall(int from_id, int reverse, t_prg *prgs);

int		ptbb_check_path(char **cmd_args, char **envp);

int		pgmb_free_strs(int from_id, char **strs);
int		pgmb_exec_progs(t_prg *prgs, char **envp);

// heredocmgr
// void	close_tmpfile(char *filename, char **argv);
// void	update_for_heredoc(int *limit, int *offset, int *flags);
// int		process_input_file(char **argv);

#endif
