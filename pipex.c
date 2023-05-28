/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:45:09 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/28 19:48:04 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	set_cmdenv_in(int head, t_cmd *cmdenvs, int argc, char **argv)
{
	if (head == 0)
	{
		cmdenvs[head].in[0] = check_and_open(argv[1], R_OK, O_RDONLY);
		cmdenvs[head].in[1] = -1;
		if (cmdenvs[head].in[0] == -1)
		{
			free(cmdenvs);
			return (-1);
		}
	}
	else
	{
		cmdenvs[head].in[0] = cmdenvs[head - 1].out[0];
		cmdenvs[head].in[1] = cmdenvs[head - 1].out[0];
	}
}

int	set_cmdenv_out(int head, t_cmd *cmdenvs, int argc, char **argv)
{
	if ((head + 1) == (argc - 3))
	{
		cmdenvs[head].out[0] = -1;
		cmdenvs[head].out[1] = check_and_open(argv[argc - 1], W_OK, O_WRONLY);
		if (cmdenvs[head].out[1] == -1)
		{
			free(cmdenvs);
			return (-1);
		}
	}
	else
	{
		if (pipe(cmdenvs[head].out == -1))
		{
			free(cmdenvs);
			return (-1);
		}
	}
}

t_cmd	*build_cmdenvs(int argc, char **argv)
{
	t_cmd	*cmdenvs;
	int		head;

	cmdenvs = ft_calloc((argc - 3) + 1, sizeof(t_cmd));
	if (cmdenvs == NULL)
		return (NULL); // Better error management please?
	head = -1;
	while (++head < (argc - 3))
	{
		cmdenvs[head].cmd = argv[head + 2];
		if (set_cmdenv_in(head, cmdenvs, argc, argv) == -1)
			return (NULL);
		if (set_cmdenv_out(head, cmdenvs, argc, argv) == -1)
			return (NULL);
	}
	cmdenvs[head].cmd = NULL; // Is that necessary?
	return (cmdenvs);
}

// 27/05 - What do you want to do?
// -- Refactor what has already been done 
// -- Implement the code to manage multiple pipes

// 29/05 - Now that build_cmdenv is somewhat written and that each cmd has an
// environment, the logic in fork_and_exec HAS to be adapted,,,
int	main(int argc, char **argv, char **envp)
{	
	t_cmd	*cmdenvs;

	if (check_argc(argc) == -1) // Should check argc == 5 or higher...
		return (1);
	cmdenvs = build_cmdenvs(argc, argv);
	if (cmdenvs == NULL)
		return (1);
	if (fork_and_exec(cmdenvs, envp) == -1)
	{
		free(cmdenvs);
		return (1);
	}
	free(cmdenvs);
	return (0);
}

// 26/05 - How to make multiple pipes work in this code?

// - Current implementation : < infile cmd1 | cmd2 > outfile
//		- < infile cmd1 1|
//		- n-1| cmdn > outfile
// 	- fork_and_exec(t_cmd cmdenv1, t_cmd cmdenv2, char **envp) manages the 
//	two cmds and their environment.

// Target implementation : < infile cmd1 | ... | cmdn > outfile
//		- < infile cmd1 1|
//		- 1| cmd2 2| (1 is an old in pipe, 2 is a new pipe)
//		- 2| cmd3 3|
//		- 3| cmd4 4|
//		- ...
//		- n-1| cmdn > outfile

// 28/05 - argc is a key on how to manage multiple pipes:
//		- if argc is 6
//			- 0 is the program name
//			- 1 is the infile
//			- 2 3 4 are commands
//			- 5 is the outfile (argc - 1)