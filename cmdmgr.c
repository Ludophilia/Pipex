/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdmgr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:39:20 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/26 19:50:27 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmdmgr.h"

char	**split_cmd(char *cmd, char **envp)
{
	char	**cmd_args;
	char	*orig_cmd;

	cmd_args = ft_split(cmd, '\x20');
	if (ft_strchr(cmd_args[0], '/') == NULL)
	{
		orig_cmd = ft_strdup(cmd_args[0]);
		cmd_args[0] = search_executable(cmd_args[0], envp);
		if (cmd_args[0] == NULL)
		{
			errno = ENOENT;
			ft_dprintf(2, "pipex: %s: command not found\n", orig_cmd);
			free(orig_cmd);
			cmd_args = NULL;
			free_strs(cmd_args, 1);
			exit(EXIT_FAILURE);
		}
	}
	else if (check_perm(cmd_args[0], X_OK) == -1)
	{
		free_strs(cmd_args, 0);
		cmd_args = NULL;
		exit(EXIT_FAILURE);
	}
	return (cmd_args);
}

void	set_fds(t_cmd cmdenv, int *infd, int *outfd)
{
	if (cmdenv.mode == 0x0)
	{
		*infd = cmdenv.files[0];
		*outfd = cmdenv.pipes[1];
		close(cmdenv.files[1]);
		close(cmdenv.pipes[0]);
	}
	else if (cmdenv.mode == 0x2)
	{
		*infd = cmdenv.pipes[0];
		*outfd = cmdenv.files[1];
		close(cmdenv.pipes[1]);
		close(cmdenv.files[0]);
	}
}

void	exec_cmd(t_cmd cmdenv, char **envp)
{
	char	**cmd_args;
	int		infd;
	int		outfd;

	cmd_args = split_cmd(cmdenv.cmd, envp);
	set_fds(cmdenv, &infd, &outfd);
	if (dup2(infd, 0) == -1 || dup2(outfd, 1) == -1
		|| execve(cmd_args[0], cmd_args, envp) == -1)
	{
		perror("pipex");
		free_strs(cmd_args, 0);
		close(infd);
		close(outfd);
		exit(EXIT_FAILURE);
	}
}

// How can you iteratively create context for the commands to run?
// --- Arrs of pids?
int	fork_and_exec(t_cmd cmdenv1, t_cmd cmdenv2, char **envp)
{
	// Don't you see a pattern...?
	int		pid_l;
	int		pid_r;
	int		ws_l;
	int		ws_r;

	pid_t	*pids;

	pids = ft_calloc(1024, sizeof(pid_t)); // metset at -1 for avoiding confusion.
	imax = 0;
	// [753, 754, 755, 0...] (Master Process POV)
	// [753, 0, 755...] (Child Process POV) (IS THAT TRUE THOUGH?)

	// Don't you see a pattern...?
	pid_l = fork();
	if (pid_l == -1)
		return (ft_perror(-1, NULL));
	else if (pid_l > 0)
	{
		pid_r = fork();
		if (pid_r == -1)
			return (ft_perror(-1, NULL));
	}

	// Don't you see a pattern...?
	if (pid_l == 0)
		exec_cmd(cmdenv1, envp); 
	else if (pid_r == 0)
		exec_cmd(cmdenv2, envp);

	// Don't you see a pattern...?
	if (pid_l > 0 && pid_r > 0)
	{
		close(cmdenv1.pipes[1]);
		close(cmdenv1.pipes[0]); 
		if (waitpid(pid_l, &ws_l, 0) == -1  || waitpid(pid_r, &ws_r, 0) == -1 
			|| (ws_r >> 8 & 0xFF) == EXIT_FAILURE
			|| (ws_l >> 8 & 0xFF) == EXIT_FAILURE)
			return (ft_perror(-1, NULL));
	}
	return (0);
}
