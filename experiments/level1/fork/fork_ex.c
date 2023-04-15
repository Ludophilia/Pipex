#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	pid_t	pid;
	
	pid = fork();
	while (1)
	{
		if (pid == 0)
			printf("Child Hello world\n");
		else
			printf("Parent Hello world\n");
		sleep(1);
	}
	return (0);
}

