/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:53:26 by jgermany          #+#    #+#             */
/*   Updated: 2025/04/22 19:21:06 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H

# define PIPEX_BONUS_H

# include <errno.h>
// # include <stdio.h>
# include <string.h>

# include <sys/wait.h>

# include <fcntl.h>

# include "../libs/libft/includes/libft.h"

# define NFILE_PERMS 00664
# define DEFAULT_PATH "/bin:/usr/bin"

typedef struct s_cmd
{
	char	*cmd;
	int		in[2];
	int		out[2];
	pid_t	pid;
}	t_cmd;

// 22/04 - sanicheck
int		ft_perror(int statuscode, char *message);
int		check_args(int argc, char **argv);
int		check_perm(char *filename, int mode);
void	free_strs(char **strs, int offset);

// cmdenvmgr
int		build_cmdenvs(t_cmd *cmdenvs, int argc, char **argv);

// cmdmgr
int	fork_and_exec(t_cmd *cmdenvs, char **envp);

// filemgr
void	close_fds(t_cmd *cmdenvs, int head, int reverse);
int		check_and_open(char *path, int openflags, mode_t openmode);
char	*search_executable(char *cmd, char **envp);

// heredocmgr
void	close_tmpfile(char *filename, char **argv);
void	update_for_heredoc(int *limit, int *offset, int *flags);
int		process_input_file(char **argv);


#endif