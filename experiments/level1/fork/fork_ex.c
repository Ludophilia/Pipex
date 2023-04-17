#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(void)
{
	pid_t	pid;
	int 	countdown;
	
	countdown = 600;
	pid = fork(); // Create a child process from the current process.
	while (countdown--)
	{
		if (pid == 0)
			printf("[PID: %i] Child Process\n", getpid());
		else
			printf("[PID: %i] Parent Process\n", getpid());
		sleep(1);
	}
	return (0);
}
