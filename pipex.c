/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:45:09 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/08 17:39:08 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Project goal - create pipex, a program that simulates the behavior
// of unix pipes...

#include "pipex.h"

// CURRENT - Manage `< <file> <command>` part (in less than 2 days)

// Any idea on how to do this?

// 	- 🔴 access to check if the file is readable
//	- open <file> with read rights
//	- dup/dup2 to close redifine 0 (STDIN_FILENO) to file's fd

//  - read data? (???? I think the program will do that by itself, just dup2
//	0 to file's fd)

// - fork
// - wait on parent
// - execve (use execpve for testing) on child

int	check_perm(char *filename, int mode)
{
	if (access(filename, mode) == -1) 
	{
		perror(filename);
		return (-1);
	}
	return (0);
}

// args are - file1 cmd1 cmd2 file2 // for now it's pipex file1 cmd1.
int		main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	ft_dprintf(2, "salut %s, tu as %i auj\n", "jeffrey", 10);
	exit (1);
	// if (argc != 3)
	// {
	// 	errno = EINVAL;
	// 	perror(NULL);
	// 	return (1);
	// }
	// if (check_perm(argv[1], F_OK) == -1 || check_perm(argv[1], R_OK) == -1)
	// 	return (1);
	// check_perm(argv[2], F_OK); // the command is usually called directly 
	// by its name, I have to resolve it first before testing if it's executable
	// or not

}
