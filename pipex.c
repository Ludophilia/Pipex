/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:45:09 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/19 21:37:29 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Project goal - create pipex, a program that simulates the behavior
// of unix pipes...

// Let's manage `< file1 cmd1` (dont forget the leak)
// 20/05 - RESUME FROM CMDMGR.C
int	main(int argc, char **argv, char **envp)
{
	if (check_argc(argc) == -1)
		return (1);
	// A pipe need to be open somewhere here, and connected to what's below
	if (redir_and_exec(argv[1], argv[2], envp) == -1)
		return (1);
	return (0);
}
