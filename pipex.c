/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:45:09 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/14 17:10:51 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Project goal - create pipex, a program that simulates the behavior
// of unix pipes...

// Let's manage `< file1 cmd1` (dont forget the leak)
int	main(int argc, char **argv)
{
	int	infile_fd;

	if (check_args(argc, argv) == -1)
		return (1);
	infile_fd = get_new_fd(argv[1], O_RDONLY); // Could be moved somewhere else
	if (infile_fd == -1)
		return (1);
	if (exec_cmd(argv[2], infile_fd) == -1)
		return (1);
	close(infile_fd);
	return (0);
}
