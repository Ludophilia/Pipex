/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanicheck.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:39:30 by jgermany          #+#    #+#             */
/*   Updated: 2023/05/21 17:12:45 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sanicheck.h"

int	ft_perror(char *message)
{
	perror(message);
	return (-1);
}

int	check_argc(int argc)
{
	if (argc != 5)
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
		return (ft_perror(filename));
	return (0);
}

void	free_strs(char **strs, int offset)
{
	char	**head;

	head = strs + offset;
	while (*head)
	{
		free(*head);
		head++;
	}
	free(strs);
}
