/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_write_ex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:45:17 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/14 22:06:22 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int	main(void)
{
	int	fd;

	fd = open("regular_file", O_CREAT, );
	if (fd == -1)
		exit(EXIT_FAILURE);
	write(fd, "Hello world\n", 11);
	
}