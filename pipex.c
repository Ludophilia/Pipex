/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:45:09 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/27 18:57:48 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// 27/05 - What do you want to do?

// -- Refactor what has already been done 
// -- Implement the code to manage multiple pipes
// -- 

// 26/05 - How to make multiple pipes work in this code?

// - Current implementation : < infile cmd1 | cmd2 > outfile
//		- < infile cmd1 1|
//		- n-1| cmdn > outfile
// - fork_and_exec(t_cmd cmdenv1, t_cmd cmdenv2, char **envp) manages the 
//	two cmds and their environment.

// Target implementation :  < infile cmd1 | ... | cmdn > outfile
//		- < infile cmd1 1| (1 infile (at the beginning))
//		- 1| cmd2 2| (1 is an old in pipe, 2 is a new pipe)
//		- 2| cmd3 3|
//		- 3| cmd4 4|
//		- ...
//		- n-1| cmdn > outfile (1 outfile (at the end))

// Remember that cmds have to be runned concurrently

// 26/05 - Why not create another context structure that contains
//		- file
//		- inpipe
//		- outpipe
// That's get refreshed at every turn (file closed, inpipe closed, 
// outpipe/inpipe swapped)

// 26/05 - Should I open files while iterating on the loop or after?
// 		- Why not during iteration? The last arg is necessarly an outpipe...
int	main(int argc, char **argv, char **envp)
{	
	int		pipes[2];
	int		files[2];

	if (check_argc(argc) == -1)
		return (1);

	// Pipe part. I will certainly move this somewhere else...	
	if (pipe(pipes) == -1)
		return (ft_perror(1, NULL));
	// File part. I will certainly move this somewhere else...
	files[0] = check_and_open(argv[1], R_OK, O_RDONLY);
	files[1] = check_and_open(argv[4], W_OK, O_WRONLY);
	if (files[0] == -1 || files[1] == -1)
		return (1);

	// fork_and_exec does < infile cmd1 | cmd2 > outfile
	if (fork_and_exec(
		(t_cmd){ .cmd = argv[2], .files = files, .pipes = pipes, .mode = 0x0 },
		(t_cmd){ .cmd = argv[3], .files = files, .pipes = pipes, .mode = 0x2 },
		envp) == -1)
		return (1);
	return (0);
}
