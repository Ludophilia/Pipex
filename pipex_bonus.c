/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:45:09 by jgermany          #+#    #+#             */
/*   Updated: 2023/06/10 20:00:00 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// 7/06 - What should be done?

// Managing here documents

//		- What is an here document ?
//			- An here document is a string that marks the end of an string 
//			(really?) gotten via 0 (/dev/stdin)

//		- But how to do that?
//			- #1
//				- Use GNL to read 0 (/dev/stdin) till the string here_doc is
//				encountered
//				- In the meantime, open and create a tempfile
//				- Write the content extracted via GNL to the file
//				- Pass the file (maybe reopen it?) to the first command,
//				- don't forget to unlink till the end...

//			- 

//				- We should test that... Why not do another experiment?
//			- ???
//		- 

// Managing appending to a file when a here_doc is used...
int	main(int argc, char **argv, char **envp)
{	
	t_cmd	cmdenvs[1024];

	if (check_argc(argc) == -1)
		return (1);
	if (build_cmdenvs(cmdenvs, argc, argv) == -1)
		return (1);
	if (fork_and_exec(cmdenvs, envp) == -1)
		return (1);
	return (0);
}
