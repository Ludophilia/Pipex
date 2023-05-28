/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdmgr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:39:20 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/28 15:53:39 by jgermany         ###   ########.fr       */
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
			free_strs(cmd_args, 1);
			cmd_args = NULL;
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
		*infd = cmdenv.in[0];
		*outfd = cmdenv.out[1];
		close(cmdenv.in[1]);
		close(cmdenv.out[0]);
	}
	else if (cmdenv.mode == 0x2)
	{
		*infd = cmdenv.out[0];
		*outfd = cmdenv.in[1];
		close(cmdenv.out[1]);
		close(cmdenv.in[0]);
	}
	// cmdenv.mode == 0x1 mode is lacking...
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
	int		pid_l;
	int		pid_r;
	int		ws_l;
	int		ws_r;

	// pid_t	pids[1024];
	// int		len;

	// len = 0;

	// Don't you see a pattern...?
	pid_l = fork();
	if (pid_l == -1)
		return (ft_perror(-1, NULL));
	if (pid_l == 0)
		exec_cmd(cmdenv1, envp); 
	if (pid_l > 0)
	{
		// close behavior depends on mode.
		close(cmdenv1.in[0]);
		close(cmdenv1.out[1]);
		if (waitpid(pid_l, &ws_l, 0) == -1 
			|| (ws_l >> 8 & 0xFF) == EXIT_FAILURE)
			return (ft_perror(-1, NULL));
	}

	// Don't you see a pattern...?
	if (pid_l > 0) // Means there a need to be aware of the parent process...e
	{
		pid_r = fork();
		if (pid_r == -1)
			return (ft_perror(-1, NULL));
		else if (pid_r == 0)
			exec_cmd(cmdenv2, envp);
		if (pid_r > 0)
		{
			// close behavior depends on mode.
			close(cmdenv2.in[1]);
			close(cmdenv2.out[0]);
			if (waitpid(pid_r, &ws_r, 0) == -1
				|| (ws_r >> 8 & 0xFF) == EXIT_FAILURE)
				return (ft_perror(-1, NULL));
		}
	}
	return (0);
}
