/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanicheck_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:39:30 by jgermany          #+#    #+#             */
/*   Updated: 2025/04/23 21:15:27 by jegerman         ###   ########.fr       */
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
		ft_eprintf("usage: pipex (<file1> | here_doc LIMITER) <cmd1>"
			" <cmd2> [cmd3...] <file2>\n");
		return (-1);
	}
	return (0);
}

int	check_perm(char *filename, int mode)
{
	if (access(filename, mode) == -1)
	{
		ft_eprintf("pipex: %s: %s\n", filename, strerror(errno));
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
