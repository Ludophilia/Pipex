/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:53:26 by jgermany          #+#    #+#             */
/*   Updated: 2025/05/04 18:26:06 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <errno.h>
# include <string.h>
# include <stdio.h> // for perror only
# include <unistd.h>

# include <stdlib.h>
# include <sys/wait.h>

# include <fcntl.h>

# include "../libs/libft/includes/libft.h"

# define DEFAULT_PATH "/bin:/usr/bin"

# define PGRS_NBR 2 + 1

# define ERR_USAGE "pipex: %s\n" "usage: pipex <file1> <cmd1> <cmd2> <file2>\n"
# define ERR_PATH "pipex: %s: %s\n"
# define ERR_GENERIC "pipex: %s\n"

# define NWFL_PRMS 00664
# define NWFL_FLGS O_CREAT | O_TRUNC | O_WRONLY

typedef enum e_dir
{
	DIR_FWD = 0,
	DIR_REV = (1 << 0)
}	t_dir;

typedef enum e_cty
{
	CHTY_PIPE = (1 << 1),
	CHTY_REDR = (1 << 2)
}	t_cty;

typedef struct s_prg
{
	char	*cmd;
	// char	*prg;
	pid_t	pid;
	int		in[2];
	t_cty	in_ty;
	int		out[2];
	t_cty	out_ty;
	// t_chn	in;
	// t_chn	out;
}	t_prg;

// 24/04 - Obsolete
typedef struct s_cmd
{
	char	*cmd;
	int		in[2];
	int		out[2];
	pid_t	pid;
}	t_cmd;


int		cmpsr_parse_progs(int argc, char **argv, t_prg *prgs);

int		fmgr_open(char *path, int openflags, mode_t openmode);
int		fmgr_close(int from, int reverse, t_prg *prgs);
int		fmgr_pipe(int fds[2]);

// cmdmgr
int		prgmgr_exec_progs(t_cmd *prgs, char **envp);

// filemgr
char	*search_executable(char *cmd, char **envp);

// 22/04 - Sanicheck (part of filemgr)?
int		check_perm(char *filename, int mode);
void	free_strs(char **strs, int offset);

#endif