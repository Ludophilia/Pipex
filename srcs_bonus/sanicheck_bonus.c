/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanicheck_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:39:30 by jgermany          #+#    #+#             */
/*   Updated: 2023/06/14 16:39:36 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sanicheck_bonus.h"

int	ft_perror(int statuscode, char *message)
{
	perror(message);
	return (statuscode);
}

int	check_args(int argc, char **argv)
{
	if (argc < 5 || (argc < 6 && (ft_strncmp(argv[1], "here_doc", 9) == 0)))
	{
		errno = EINVAL;
		perror("pipex");
		ft_dprintf(2, "usage: pipex (<file1> | here_doc LIMITER) <cmd1>"
			" <cmd2> [cmd3...] <file2>\n");
		return (-1);
	}
	return (0);
}

int	check_perm(char *filename, int mode)
{
	if (access(filename, mode) == -1)
	{
		ft_dprintf(2, "pipex: %s: %s\n", filename, strerror(errno));
		return (-1);
	}
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
