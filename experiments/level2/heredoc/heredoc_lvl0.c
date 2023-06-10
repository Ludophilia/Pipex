/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 13:49:12 by jgermany          #+#    #+#             */
/*   Updated: 2023/06/10 16:01:53 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define RW_SIZE 20

// Would be smarter to use GNL no, instead of just read...
// that way, your read/write will work for every buffer size, eh.
// Do the exp again but with gnl... A sort of level 1 or 2...
int	get_user_input(int temp_fd, ssize_t	*is_done)
{
	char	buffer[BUFFER_SIZE];

	if (is_done == NULL)
		return (-1);
	if (write(0, "> ", 2) == -1 || read(0, buffer, RW_SIZE) == -1)
		return (-1);
	*is_done = strncmp("here_doc\n", buffer, 10) == 0;
	if (*is_done)
		return (0);
	if (write(temp_fd, buffer, RW_SIZE) == -1)
		return (-1);
	return (1);
}

// unlink("temp"); // Remove the temp file at the end
int	main(void)
{
	int		temp_fd;
	ssize_t	is_done;
	int		uinput_res;

	temp_fd = open("temp", O_CREAT | O_RDWR, 00664);
	if (temp_fd == -1)
		return (1);
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
