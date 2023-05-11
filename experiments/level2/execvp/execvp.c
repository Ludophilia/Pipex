#include <unistd.h>
#include <sys/wait.h>

int	main(void)
{
	pid_t	pid;

	pid = fork();
	if (pid)
	{
		execvp(
			"echo",
			(char *[]){
				"echo",
				"1",
				"2",
				"3",
				"4",
				"5",
				"WWWWWWWWWOOOWOOWOOWOW",
				NULL}
		);
	}
	else {
		wait(NULL);
	}
	return (0);
}

// execvp(
// 	"git",
// 	(char *[]){
// 		"git",
// 		"log",
// 		NULL}
// );

// execvp(
// 	"git",
// 	(char *[]){
// 		"git",
// 		"clone",
// 		"git@github.com:Ludophilia/example.git",
// 		NULL}
// );

// execvp(
// 	"echo",
// 	(char *[]){
// 		"echo",
// 		"1",
// 		"2",
// 		NULL}
// );

// execvp(
// 	"ps",
// 	(char *[]){
// 		"ps",
// 		"-f",
// 		"-t",
// 		"s000",
// 		NULL
// 		}
// );