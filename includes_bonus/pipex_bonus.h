/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:53:26 by jgermany          #+#    #+#             */
/*   Updated: 2025/05/18 20:49:24 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H

# define PIPEX_BONUS_H

# include "../includes/pipex.h"

# define PGRB_NBR (1024 + 1)

# define USGB_SUGG "usage: pipex <file1> <cmd1> ... <cmdn> <file2>\n"

# define ERRB_USAGE (ERR_GNR USGB_SUGG)

# define APN_FLGS (O_CREAT | O_APPEND | O_WRONLY)

typedef enum e_ctb
{
	CHTB_HERE = (1 << 1),
	CHTB_REDR = (1 << 2),
	CHTB_APPN = (1 << 3),
	CHTB_PIPE = (1 << 4)
}	t_ctb;

typedef struct s_pgb
{
	char	*cmd;
	pid_t	pid;
	int		in[2];
	int		out[2];
	t_ctb	in_ty;
	t_ctb	out_ty;
}	t_pgb;

int		psrb_parse_progs(int argc, char **argv, t_pgb *prgs);

int		fmgb_open(char *path, int openflags, mode_t openmode);
int		fmgb_close(int *prg_fds, int end);
int		fmgb_pipe(int fds[2]);
int		fmgb_access(char *path, int type);
int		fmgb_closeall(int from_id, int reverse, t_pgb *prgs);

int		ptbb_check_path(char **cmd_args, char **envp);

int		pgmb_free_strs(int from_id, char **strs);
int		pgmb_exec_progs(t_pgb *prgs, char **envp);

// heredocmgr
// void	close_tmpfile(char *filename, char **argv);
// void	update_for_heredoc(int *limit, int *offset, int *flags);
// int		process_input_file(char **argv);
int		hrm_open_heredoc(char **argv);

#endif
