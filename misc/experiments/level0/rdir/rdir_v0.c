#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int	main(int argc, char **argv)
{
	int		fd;
	ssize_t	bytesread;
	char	buffer[1024];

	if (argc != 2)
	{
		dprintf(2, "Wrong number of arguments\n"
				"usage: test <path>\n");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("test0 open errror");
		return (1);
	}
	if (memset(buffer, 0, 1024) == NULL)
	{
		dprintf(2, "arr init error");
		return (1);
	}
	bytesread = read(fd, buffer, 10);
	while (bytesread)
	{
		if (bytesread == - 1)
		{
			perror("test0 read errror");
			return (1);
		}
		printf("%s", buffer);
		bytesread = read(fd, buffer, 10);
	}
	close(fd);
	return (0);
}
