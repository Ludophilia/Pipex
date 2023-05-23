/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:45:09 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/23 17:57:34 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Project goal - create pipex, a program that simulates the behavior
// of unix pipes...

// Let's manage `| cmd2`, and then `> file2`



//  23/05 - CLOSE THE FDS AT EVERY LEVEL!!!!!!!!!
// IT USES RESSOURCES AND I DON'T GET THE PROMPT BACKKK/
// MAYBE BECAUSE THE opened file is left open?
int	main(int argc, char **argv, char **envp)
{	
	int		pipes[2]; // 0 read, 1 write...
	int		files[2]; // 0 read, 1 write...

	// ft_dprintf(2, "[%i [%i]]=======START OF PROGRAM======\n", getpid(), getppid());
	if (check_argc(argc) == -1)
		return (1);

	// Be smart about which file descriptor you open and at what level...
	// PIPES - must be at parent level, as they are a bridge between processes)
	if (pipe(pipes) == -1)
		return (ft_perror(1, NULL));

	// How about files?
	// < file1 and > file2. file1 and file2 should be created right?
	// Maybe doing this at this level explains why the prompt is not
	// given back...
	files[0] = check_and_open(argv[1], R_OK, O_RDONLY);
	files[1] = check_and_open(argv[4], W_OK, O_WRONLY);
	if (files[0] == -1 || files[1] == -1)
		return (-1);

	// ft_dprintf(2, "files[0]: %i, files[1]: %i\n", files[0], files[1]);
	// ft_dprintf(2, "pipes[0]: %i, pipes[1]: %i\n", pipes[0], pipes[1]);

	if (fork_and_exec(
		(t_cmd){ .cmd = argv[2], .files = files, .pipes = pipes, .mode = 0x0 },
		(t_cmd){ .cmd = argv[3], .files = files, .pipes = pipes, .mode = 0x2 },
		envp) == -1)
		return (1);

	// Be smarter...
	close(files[0]);
	close(files[1]);
	// close(pipes[0]);
	// close(pipes[1]);
	// ft_dprintf(2, "[%i [%i]]=======END OF PROGRAM======\n", getpid(), getppid());
	return (0);
}
