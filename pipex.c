/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:45:09 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/22 14:01:55 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Project goal - create pipex, a program that simulates the behavior
// of unix pipes...

// Let's manage `| cmd2`, and then `> file2`

// We dreadfully lack experience, so let's start 
// by managing files and pipe at this level then we will see
// what happens...
int	main(int argc, char **argv, char **envp)
{
	int		infd;
	int		fds[2];
	int		outfd;
	
	if (check_argc(argc) == -1)
		return (1);

	// < file1 and > file2. file1 and file2 should be created right?

	// Not necessary at PARENT level right?
	//	- What's for? This descriptor should be open before a command read/write
	// from STDIN/STDOUT (hijacked via dup2 of course)


	// The struct s_cmd could use filenames (char *) the same way it uses paths
	// for cmds right? Besides, they could be used for triggering reading/
	// writing on a pipe.
	// 		- if (!infile) use the read end of the pipe
	// 		- if (!outfile) use the write end of the pipe

	if (pipe(fds) == -1) // MUST BE AT PARENT LEVEL (BRIDGE BETWEEN PROCESSES)
		return (ft_perror(NULL, 1));
	// outfd = check_and_open(argv[4], W_OK, O_WRONLY);
	// if (outfd == -1)
	// 	return (1);

	// NOW we should understand how to manage those close() syscalls.
	if (fork_and_exec(
		(t_cmd){ .cmd = argv[2], .inf = argv[1], .outf = NULL },
		(t_cmd){ .cmd = argv[3], .inf = NULL, .outf = argv[4]},
		envp) == -1)
		return (1);

	// close(infd);
	// close(outfd);
	return (0);
}
