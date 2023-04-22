/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fl_ex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:27:08 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/22 11:41:42 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define FILENAME "level0/fl/new_file"
#define FORBIDDEN "level0/fl/forbidden_file"

int		access_checker(const char *filename)
{
	int	errord;

	errord = 0;
	if (access(FILENAME, F_OK) == 0)
		printf("%s exists.\n", filename);
	else
	{
		printf("%s doesn't exist 😂\n", filename);
		errord = 1;
	}
	if (access(FILENAME, R_OK) == 0)
		write(1, "The process has read access.\n", 29);
	if (access(FILENAME, W_OK) == 0)
		write(1, "The process has write access.\n", 30);
	if (access(FILENAME, X_OK) == 0)
		write(1, "The process has execute access.\n", 32);
	if (errord)
		return (-1);
	return (0);
}

/* Phase 0 - Let's tinker with open, its flags and the octal access modes, and
then use access to test if the file exists and what access rights the process
has. */
int		fl_phase0(const int rights)
{
	int	fd;

	write(1, "\n", 1);
	fd = open(FILENAME, O_CREAT | O_RDWR, rights);
	if (fd == -1)
		return (-1);
	if (access_checker(FILENAME) == -1)
		return (-1);
	close(fd);
	unlink(FILENAME);
	return (0);
}

/* Phase 1 - Open an unopenable file with 0_RDWR flag. Can I even use access 
while doing this? */
int		fl_phase1(void)
{
	int	fd;

	write(1, "\n", 1);
	fd = open(FORBIDDEN, 0x202, 0);
	if (fd == -1)
	{
		write(1, "Couldn't open file, process don't have rights.\n", 48);
		close(fd);
	}
	if (access_checker(FORBIDDEN) == -1)
	{
		unlink(FORBIDDEN); // Still can remove it.
		close(fd);
		return (-1);
	}
	return (0);
}

int		main(void)
{
	int	rights;

	rights = 0600; // Change the octal value as much as you want. Still can use 
	// S_IURWX FLAGS as well.
	if (fl_phase0(rights) == -1) 
		exit(EXIT_FAILURE);
	if (fl_phase1() == -1)
		return (1);
	return (0);
}