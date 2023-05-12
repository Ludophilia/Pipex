/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanicheck.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:39:30 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/11 22:53:52 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sanicheck.h"

int		check_perm(char *filename, int mode)
{
	if (access(filename, mode) == -1) 
	{
		perror(filename);
		return (-1);
	}
	return (0);
}

int		check_argc(int argc)
{
	if (argc != 3)
	{
		errno = EINVAL;
		perror("pipex");
		ft_dprintf(2, "usage: pipex <file1> <cmd1> <cmd2> <file2>\n");
		return (-1);
	}
	return (0);
}

int		check_args(int argc, char **argv)
{
	if (check_argc(argc))
		return (-1);
	if (check_perm(argv[1], F_OK) == -1 || check_perm(argv[1], R_OK) == -1)
		return (-1);
	// Where is the part that tests if cmds is valid or not?
	return (0);
}
