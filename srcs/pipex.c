/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:45:09 by jgermany          #+#    #+#             */
/*   Updated: 2023/06/15 12:04:35 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
