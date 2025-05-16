/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:45:09 by jgermany          #+#    #+#             */
/*   Updated: 2025/05/16 20:30:29 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// 16/05 - OK. Let's manage the bonus phase.
// = First, let's unlock the ability to manage multiple pipes
// = Then we will improve heredoc management by streamlining the logic
int	main(int argc, char **argv, char **envp)
{
	t_prg	prgs[PGRB_NBR];

	if ((++argv, --argc, argc < 4) && ft_eprintf(ERRB_USAGE, strerror(EINVAL)))
		return (1);
	if (psrb_parse_progs(argc, argv, prgs) == -1)
		return (2);
	if (pgmb_exec_progs(prgs, envp) == -1)
		return (3);
	return (0);
}
