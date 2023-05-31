/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdmgr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:39:20 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/31 21:19:55 by jgermany         ###   ########.fr       */
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

void	close_fds(t_cmd *cmdenvs)
{
	int	head;

	head = -1;
	while (cmdenvs[++head].cmd)
	{
		close(cmdenvs[head].in[0]);
		close(cmdenvs[head].out[1]);
		if (cmdenvs[head].in[1] != -1)
			close(cmdenvs[head].in[1]);
		if (cmdenvs[head].out[0] != -1)
			close(cmdenvs[head].out[0]);
	}
}

void	exec_cmd(t_cmd *cmdenvs, int head, char **envp)
{
	char	**cmd_args;
	int		infd;
	int		outfd;

	cmd_args = split_cmd(cmdenvs[head].cmd, envp);
	infd = cmdenvs[head].in[0];
	outfd = cmdenvs[head].out[1];
	if (dup2(infd, 0) == -1 || dup2(outfd, 1) == -1)
	{
		perror("pipex");
		free_strs(cmd_args, 0);
		close_fds(cmdenvs);
		exit(EXIT_FAILURE);
	}
	close_fds(cmdenvs);
	if (execve(cmd_args[0], cmd_args, envp) == -1)
	{
		perror("pipex");
		free_strs(cmd_args, 0);
		exit(EXIT_FAILURE);
	}
}

int	wait_cmds(t_cmd *cmdenvs, int head)
{
	int		ws;

	ws = -1;
	while (--head >= 0)
	{
		if (waitpid(cmdenvs[head].pid, &ws, 0) == -1
			|| (ws >> 8 & 0xFF) == EXIT_FAILURE)
			return (ft_perror(-1, "c'est ça - error propagation")); // IMPROVE ERR MANAGEMENT
		printf("[DEBUG] ws == %i from pid == %i\n", ws, cmdenvs[head].pid); // REMOVE
	}
	return (0);
}

int	fork_and_exec(t_cmd *cmdenvs, char **envp)
{
	pid_t	lastpid;
	int		head;

	head = -1;
	lastpid = -1;
	while (cmdenvs[++head].cmd)
	{
		if (head == 0 || lastpid > 0)
		{
			lastpid = fork();
			if (lastpid > 0)
			{
				close(cmdenvs[head].in[0]);
				close(cmdenvs[head].out[1]);
				cmdenvs[head].pid = lastpid;
			}
			else if (lastpid == -1)
				return (ft_perror(-1, NULL));
			else if (lastpid == 0)
				exec_cmd(cmdenvs, head, envp);
		}
	}
	if (lastpid > 0 && wait_cmds(cmdenvs, head) == -1)
		return (ft_perror(-1, "C'est ça aussi - error propagation")); // IMPROVE ERR MANAGEMENT
	return (0);
}
