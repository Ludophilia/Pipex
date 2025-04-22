#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>

int	main(int argc, char **argv)
{
	DIR				*dir;
	struct dirent	*dirent;
	char			buffer[1024];

	if (argc != 2)
	{
		dprintf(2, "Wrong number of arguments\n"
			"usage: test <path>\n");
		return (1);
	}
	dir = opendir(argv[1]);
	if (dir == NULL)
	{
		perror(NULL);
		return (1);
	}
	dirent = readdir(dir);
	while (dirent)
	{
		printf("%s\n", dirent->d_name);
		dirent = readdir(dir);
	}
	closedir(dir);
	return (0);
}
