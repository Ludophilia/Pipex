/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:45:09 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/07 19:38:04 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Project goal - create pipex, a program that simulates the behavior
// of unix pipes...

#include "pipex.h"

// CURRENT - Manage `< <file> <command>` part (in less than 2 days)

// Any idea on how to do this?

// 	- access to check if the file is readable
//	- open <file> with read rights 
//	- dup/dup2 to close redifine 0 (STDIN_FILENO) to file's fd

//  - read data? (???? I think the program will do that by itself, just dup2
//	0 to file's fd) 

// - fork 
// - wait on parent
// - execve (use execpve for testing) on child

// void	test(void)
// {
	
// }


int		main(int argc, char **argv, char **envp)
{
	// args are - file1 cmd1 cmd2 file2
	// for now it's pipex file1 cmd1.
	(void)envp;
	if (argc != 3)
		return (1); // Please manage this better.
	// Check that file1 is readable and cmd1 is executable by the process
	// cmd1 has to be managed differently
	if (access(argv[1], F_OK) == -1 || access(argv[2], F_OK) == -1) 
	{
		perror(NULL); // Please manage this better. Add <filename> for ex.
		return (-1);
	}
	// ft_printf(
	// 	"[DEBUG] argc: %i, *argv: %s, *envp: %s\n",
	// 	argc, *argv, *envp
	// );
}
