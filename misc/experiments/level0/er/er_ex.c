/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   er_ex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 11:56:24 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/22 13:59:26 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#define BEST_GIRL🇩🇪 "evangelion/characters/asuka_langley"

/* Perror walkthough. This starts with a purposefully faulty syscall that will
return -1 and set errno to a certain value. */
void	perror_ex(void)
{
	if (open(BEST_GIRL🇩🇪, O_WRONLY) != -1)
		return ;
	perror(0);
	perror("Sring argument that will be printed first, followed by"
		" a colon and a blank, then the error message corresponding"
		" to the current value of errno followed by a newline");
	printf("The error message can be accessed via"
		" sys_errlist[errno] too: '%s'\n", sys_errlist[errno]);
	printf("\n");
}

/* Strerror walkthough. This starts with a purposefully faulty syscall that will
return -1 and set errno to a certain value. */
void	strerr_ex(void)
{
	if (open(BEST_GIRL🇩🇪, O_WRONLY) != -1)
		return ;
	printf("strerror takes errno as an arg and retuns the corresponding "
	"error message: %s\n", strerror(errno));
	printf("%s\n", strerror(errno));
	printf("%s\n", sys_errlist[errno]);
	printf("\n");
}

void	conclusion(int error_number)
{
	perror(0);
	dprintf(2, "%s\n", strerror(error_number));
	dprintf(2, "%s\n", sys_errlist[error_number]);
	printf("\n");
}

int		main(void)
{
	perror_ex();
	strerr_ex();
	conclusion(errno);
	conclusion(-1);
}