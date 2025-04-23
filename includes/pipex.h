/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:53:26 by jgermany          #+#    #+#             */
/*   Updated: 2025/04/23 20:32:23 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <errno.h>
# include <string.h>
# include <stdio.h>
// # include <unistd.h>

# include <stdlib.h>
# include <sys/wait.h>

# include <fcntl.h>

# include "../libs/libft/includes/libft.h"

# define NFILE_PERMS 00664
# define DEFAULT_PATH "/bin:/usr/bin"

# define ERR_USAGE "pipex: %s\nusage: pipex <file1> <cmd1> <cmd2> <file2>\n"

typedef struct s_cmd
{
	char	*cmd;
	int		in[2];
	int		out[2];
	pid_t	pid;
}	t_cmd;

// 22/04 - Sanicheck
int		ft_perror(int statuscode, char *message);
// int		check_argc(int argc);
int		check_perm(char *filename, int mode);
void	free_strs(char **strs, int offset);

// Cmdenvmgr
int		build_cmdenvs(t_cmd *cmdenvs, int argc, char **argv);

// cmdmgr
int		fork_and_exec(t_cmd *cmdenvs, char **envp);

// filemgr
void	close_fds(t_cmd *cmdenvs, int head, int reverse);
int		check_and_open(char *path, int openflags, mode_t openmode);
char	*search_executable(char *cmd, char **envp);

#endif