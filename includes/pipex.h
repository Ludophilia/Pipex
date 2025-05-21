/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:53:26 by jgermany          #+#    #+#             */
/*   Updated: 2025/05/21 20:09:05 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <errno.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>

# include "../libs/libft/includes/libft.h"

# define ENV_PATH_DFLT "/bin:/usr/bin"

# define PGRS_NBR 3

# define FL_PRMS 00664

# define ERR_GNR "pipex: %s\n"
# define ERR_PTH "pipex: %s: %s\n"
# define ERR_CMD "pipex: %s: command not found\n"
# define ERR_USAGE "pipex: %s\n \
	usage: pipex <file1> <cmd1> <cmd2> <file2>\n"

typedef enum e_ffl
{
	FL_FLGS = (O_CREAT | O_TRUNC | O_WRONLY),
}	t_ffl;

typedef enum e_dir
{
	DIR_FWD = 0,
	DIR_REV = (1 << 0)
}	t_dir;

typedef struct s_prg
{
	char	*cmd;
	pid_t	pid;
	int		in[2];
	int		out[2];
}	t_prg;

int		psr_parse_progs(int argc, char **argv, t_prg *prgs);

int		fmg_open(char *path, int openflags, mode_t openmode);
int		fmg_close(int *prg_fds, int end);
int		fmg_pipe(int fds[2]);
int		fmg_access(char *path, int type);
int		fmg_closeall(int from_id, int reverse, t_prg *prgs);

int		ptb_check_path(char **cmd_args, char **envp);

int		pgm_free_strs(int from_id, char **strs);
int		pgm_exec_progs(t_prg *prgs, char **envp);

#endif
