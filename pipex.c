/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:45:09 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/29 16:08:20 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Project goal - create pipex, a program that simulates the behavior
// of unix pipes...

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	ft_printf(
		"[DEBUG] argc: %i, *argv: %s, *envp: %s\n",
		argc, *argv, *envp
	);
}