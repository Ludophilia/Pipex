/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:26:11 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/20 13:05:43 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

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
	char	buffer[1024];
	
	confstr(_CS_PATH, buffer, 1024);
	printf("_CS_PATH='%s'\n", buffer);
	print_envvars(0, envp);
	print_envvars(0, environ);
    return (0);
}
