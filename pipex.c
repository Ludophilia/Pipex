/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:45:09 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/21 17:13:26 by jgermany         ###   ########.fr       */
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

// What I need. Get fds from 
	// An infile
	// A set of pipe
		
int	main(int argc, char **argv, char **envp)
{
	int		infd;
	int		fds[2];
	int		outfd;
	
	if (check_argc(argc) == -1)
		return (1);

	infd = check_and_open(argv[1], R_OK, O_RDONLY);
	if (infd == -1)
		return (1);
	
	if (pipe(fds) == -1)
		return (ft_perror(NULL));
		
	outfd = check_and_open(argv[4], W_OK, O_RDONLY);
	if (outfd == -1)
		return (1);

	if (fork_and_exec(
		(t_cmd){ .cmd = argv[2], .infd = infd, .outfd = fds[1] },
		(t_cmd){ .cmd = argv[3], .infd = fds[0], .outfd = outfd },
		envp) == -1)
		return (1);

	return (0);
}
