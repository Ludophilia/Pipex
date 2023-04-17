/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rw_ex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:45:17 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/17 21:29:48 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rw_ex.h"

// Restart exeperiments from there. Divide this into multiple functions. 
int	main(void)
{
	int		fd;
	char	*buffer;

	fd = open("level0/rw/regular_file", O_RDWR|O_CREAT,
		S_IRWXU|S_IRWXG|S_IRWXO);
	buffer = malloc(BUFFER_SIZE * sizeof(char));
	if (fd == -1 || !buffer)
		exit(EXIT_FAILURE);
		
	printf("\nPHASE ONE:\n");

	write(fd, "Hello world\n", 4); // read and write share the same head pos.

	lseek(fd, -4, SEEK_CUR); // reset to 0 for next read syscall
	printf("read status: %li\n", read(fd, buffer, 4));

	dprintf(1, "Buffer: '%s'\n", buffer);

	printf("\nPHASE TWO:\n");

	lseek(fd, 0, SEEK_SET); // reset to 0 for next write syscall
	write(fd, "Hello world\n", 11); 

	lseek(fd, -10, SEEK_END); // Head to e
	printf("read status: %li\n", read(fd, buffer, 11)); // buffer is rewritten

	fprintf(stdout, "Buffer: '%s'\n", buffer);
	close(fd);
}
