/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_lvl1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:06:56 by jgermany          #+#    #+#             */
/*   Updated: 2023/06/11 21:13:07 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libft/libft.h"

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

int	get_user_input(int temp_fd, ssize_t	*is_done)
{
	char	*buffer;

	if (is_done == NULL)
		return (-1);
	if (write(0, "> ", 2) == -1)
		return (-1);
	buffer = get_next_line(0);
	if (buffer == NULL)
		return (-1);
	*is_done = strncmp("here_doc\n", buffer, 10) == 0;
	if (*is_done)
	{
		free(buffer);
		return (0);
	}
	if (write(temp_fd, buffer, ft_strlen(buffer)) == -1)
	{
		free(buffer);
		return (-1);
	}
	free(buffer);
	return (1);
}

// Don't forget to unlink tmp...
int	main(void)
{
	int		temp_fd;
	ssize_t	is_done;
	int		uinput_res;

	temp_fd = open("tmp", O_CREAT | O_RDWR, 00664);
	if (temp_fd == -1)
		return (1); // close fd?
	uinput_res = get_user_input(temp_fd, &is_done);
	if (uinput_res == -1)
		return (1);
	else if (uinput_res == 0)
		return (0);
	while (is_done == 0)
	{
		uinput_res = get_user_input(temp_fd, &is_done);
		if (uinput_res == -1)
			return (1);
		else if (uinput_res == 0)
			return (0);
	}
	close(temp_fd);
	return (0);
}
