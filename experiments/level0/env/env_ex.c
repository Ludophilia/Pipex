/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:26:11 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/28 12:19:57 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

extern char	**environ;

void	print_envvars(unsigned lets_go, char **envptr)
{
	if (!lets_go)
		return ;
    while (*envptr)
        printf("%s\n", *envptr++);
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	char	**with_envp;
	char	**with_environ;
	
	with_envp = envp;
	with_environ = environ;
	print_envvars(0, with_envp);
	print_envvars(0, with_environ);
    return (0);
}
