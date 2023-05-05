#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int	count;

	if (argc != 2)
	{
		dprintf(2, "Invalid number of args.\n"
			"USAGE: ./countdown <secs>\n");
		exit(1);
	}
	count = atoi(argv[1]);
	if (!count)
	{
		dprintf(2, "Invalid args.\n"
			"USAGE: ./countdown <secs>\n");
		exit(1);
	}
	while (count)
	{
		printf("%i\n", count--);
		sleep(1);
	}
	return (0);
}
