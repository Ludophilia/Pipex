/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:45:09 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/22 20:02:42 by jgermany         ###   ########.fr       */
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
	if (check_argc(argc) == -1)
		return (1);

	if (fork_and_exec(
		(t_cmd){ .cmd = argv[2], .inf = argv[1], .mode = 0x0 },
		(t_cmd){ .cmd = argv[3], .outf = argv[4], .mode = 0x2 },
		envp) == -1)
		return (1);

	// close(infd); //
	// close(outfd);
	return (0);
}
