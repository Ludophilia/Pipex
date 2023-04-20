/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rw_ex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:45:17 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/19 15:45:30 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rw_ex.h"
#define FILENAME "level0/rw/regular_file"

/* Phase 0: lets create and open a file, try to write to it and then read
	from it... Let's learn the importance of lseek in the process... */
int	rw_phase0(void)
{
	int		fd;
	char	*buffer;
	ssize_t	bread;

	fd = open(FILENAME, O_RDWR | O_CREAT,
			S_IRWXU | S_IRWXG | S_IRWXO);
	buffer = malloc(BUFFER_SIZE * sizeof(char));
	if (fd == -1 || !buffer)
		return (-1);
	if (write(fd, "Hello world\n", 4) == -1 || lseek(fd, -4, SEEK_CUR) == -1)
		return (-1);
	bread = read(fd, buffer, 4);
	if (bread == -1)
		return (-1);
	printf("(bread: %li)\n", bread);
	dprintf(1, "Buffer: '%s'\n\n", buffer);
	free(buffer);
	return (fd);
}

/* Phase 1: Does an open() call dies when a function has finished execution?
Let's keep experimenting with read/write with more lseek() variants. */
int	rw_phase1(int fd)
{
	char		*buffer;
	ssize_t		bread;

	buffer = malloc(BUFFER_SIZE * sizeof(char));
	if (!buffer || fd == -1)
		return (-1);
	if (lseek(fd, 0, SEEK_SET) == -1 || write(fd, "Hello world\n", 11) == -1)
		return (-1);
	if (lseek(fd, -10, SEEK_END) == -1)
		return (-1);
	bread = read(fd, buffer, 11);
	if (bread == -1)
		return (-1);
	printf("(bread: %li)\n", bread);
	fprintf(stdout, "Buffer: '%s'\n\n", buffer);
	return (fd);
}

/* Phase 2: What does close do? How does it affect the subsequent
read/write/lseek calls...? */
int	rw_phase2(int fd)
{
	close(fd);
	if (write(fd, "How you're doing?\n", 18) == -1)
		return (-1);
	return (fd);
}

int	main(void)
{
	int	fd;

	fd = rw_phase0();
	if (fd == -1)
		exit(EXIT_FAILURE);
	if (rw_phase1(fd) == -1)
		exit(EXIT_FAILURE);
	if (rw_phase2(fd) == -1)
		write(1, "The write call should normally fail.\n", 37);
	if (unlink(FILENAME) == -1)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
