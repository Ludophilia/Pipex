/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:45:09 by jgermany          #+#    #+#             */
/*   Updated: 2025/04/24 15:24:10 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// 22/04 = Again, let's make that clearer and even more compact

// - [ ] Do not forget to rename files and add the prefix so those functions 
// are easily

int	main(int argc, char **argv, char **envp)
{	
	// t_cmd	cmdenvs[2 + 1];

	if ((++argv, --argc, argc != 4) && ft_eprintf(ERR_USAGE, strerror(EINVAL)))
		return (1);


	(void)envp;


	// 23/04 - 
	// if (build_cmdenvs(cmdenvs, argc, argv) == -1)
	// 	return (2);

	
	// if (fork_and_exec(cmdenvs, envp) == -1)
	// 	return (3);


	return (0);
}
