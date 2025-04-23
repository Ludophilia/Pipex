/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanicheck.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:39:30 by jgermany          #+#    #+#             */
/*   Updated: 2025/04/23 21:18:08 by jegerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_perm(char *filename, int mode)
{
	if (access(filename, mode) == -1)
	{
		ft_eprintf("pipex: %s: %s\n", filename, strerror(errno));
		return (-1);
	}
	return (0);
}

// 23/04 - Too complicated, not ereganto 
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
