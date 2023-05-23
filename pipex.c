/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:45:09 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/23 19:04:09 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{	
	int		pipes[2];
	int		files[2];

	if (check_argc(argc) == -1)
		return (1);

	// Be smart about which file descriptor you open and at what level...
	// Pipe part. I will certainly move this somewhere else...	
	if (pipe(pipes) == -1)
		return (ft_perror(1, NULL));

	// File part. I will certainly move this somewhere else...
	files[0] = check_and_open(argv[1], R_OK, O_RDONLY);
	files[1] = check_and_open(argv[4], W_OK, O_WRONLY);
	if (files[0] == -1 || files[1] == -1)
		return (-1);

	if (fork_and_exec(
		(t_cmd){ .cmd = argv[2], .files = files, .pipes = pipes, .mode = 0x0 },
		(t_cmd){ .cmd = argv[3], .files = files, .pipes = pipes, .mode = 0x2 },
		envp) == -1)
		return (1);

	// Be smarter...
	close(files[0]);
	close(files[1]);
	return (0);
}
