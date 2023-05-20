/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanicheck.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:39:30 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/20 13:51:50 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sanicheck.h"

int	check_argc(int argc)
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

int	check_perm(char *filename, int mode)
{
	if (access(filename, mode) == -1)
	{
		perror(filename);
		return (-1);
	}
	return (0);
}

void	free_strs(char **strs)
{
	char	**head;
	
	head = strs;
	while (*head)
	{
		free(*head);
		head++;
	}
	free(strs);
}
