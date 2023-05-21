/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:45:09 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/21 13:52:13 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Project goal - create pipex, a program that simulates the behavior
// of unix pipes...

// Let's manage `| cmd2`
// And then `> file2`

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

	// What I need. Get fds from 
		// An infile
		// A set of pipe
		
	infd = check_and_open(argv[1], R_OK, O_RDONLY);
	if (infd == -1)
		return (-1);
	
	if (pipe(fds) == -1)
	{
		perror(NULL);
		return (-1);
	}
	outfd = fds[1];

	// A pipe need to be open somewhere here, and connected to what's below
	if (fork_and_exec(argv[2], infd, outfd, envp) == -1)
		return (1);
	infd = fds[0];
	if (fork_and_exec(argv[3], infd, 1, envp) == -1)
		return (1);

	return (0);
}
