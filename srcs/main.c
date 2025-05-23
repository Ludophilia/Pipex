/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:45:09 by jgermany          #+#    #+#             */
/*   Updated: 2025/05/16 17:33:39 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_prg	prgs[PGRS_NBR];

	if ((++argv, --argc, argc != 4) && ft_eprintf(ERR_USAGE, strerror(EINVAL)))
		return (1);
	if (psr_parse_progs(argc, argv, prgs) == -1)
		return (2);
	if (pgm_exec_progs(prgs, envp) == -1)
		return (3);
	return (0);
}
