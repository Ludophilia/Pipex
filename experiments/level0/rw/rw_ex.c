/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rw_ex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:45:17 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/18 23:43:16 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rw_ex.h"

int	rw_level0(void)
{
	int		fd;
	char	*buffer;

	fd = open("level0/rw/regular_file", O_RDWR|O_CREAT,
		S_IRWXU|S_IRWXG|S_IRWXO);
	buffer = malloc(BUFFER_SIZE * sizeof(char));
	if (fd == -1 || !buffer)
		return(-1);
	if (write(fd, "Hello world\n", 4) == -1 || lseek(fd, -4, SEEK_CUR) == -1)
		return(-1); // reset to 0 for next read syscall
	printf("(bread: %li)\n", read(fd, buffer, 4));
	dprintf(1, "Buffer: '%s'\n\n", buffer);
	free(buffer);
	return (fd);
}

int	rw_level1(int fd)
{
	char		*buffer;
	ssize_t		bread;
	
	buffer = malloc(BUFFER_SIZE * sizeof(char));
	if (!buffer || fd == -1)
		return (-1);
	if (lseek(fd, 0, SEEK_SET) == -1 || write(fd, "Hello world\n", 11) == -1)
		return (-1);  // resetted to 0 for next write syscall
	if (lseek(fd, -10, SEEK_END) == -1)
		return (-1);
	bread = read(fd, buffer, 11);  // buffer is rewritten
	if (bread == -1)
		return (-1);
	printf("(bread: %li)\n", bread);
	fprintf(stdout, "Buffer: '%s'\n", buffer);
	close(fd);
	return (0);
}

int	main(void)
{
	int	fd;

	fd = rw_level0();
	if (fd == -1)
		exit(EXIT_FAILURE);
	if (rw_level1(fd) == -1)
		exit(EXIT_FAILURE);
}
