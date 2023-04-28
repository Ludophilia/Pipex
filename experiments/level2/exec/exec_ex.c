/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgermany <nyaritakunai@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:52:10 by jgermany          #+#    #+#             */
/*   Updated: 2023/04/28 13:59:26 by jgermany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/* 
What to do?
	- explore the exec(l|v)[p][e] family
	- level0 : just use execve,
	- level0,5: show the difference with something like execlpe
	- level1 : use it within a child process  
*/

/* Level0 - Just a simple pick up of execve(2) the og of the exec family.
execve takes the full path to the program or script to execute, an array of 
strings staring with the prog name, then the args to the program, then null,
and an array of environment variables...*/
int	exec_level0(unsigned letsgo, char **envp)
{
	char	*program;
	char	**args;
	
	if (!letsgo)
		return (0);
	program = "/usr/bin/ls";
	args = (char *[]){program, "-pm", NULL};
	if (execve(program, args, envp) == -1)
		return (-1);
	write(1, "This should not be printed!\n", 28);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	if (exec_level0(1, envp) == -1)
		return (-1);
	return (0);
}