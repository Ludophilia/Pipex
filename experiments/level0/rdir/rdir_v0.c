#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int     main(int argc, char **argv)
{
        int             fd;
        ssize_t bytesread;
        char    buffer[1024];

        if (argc != 2)
        {
                dprintf(2, "Wrong number of arguments\n"
                        "usage: test <path>\n");
                return (1);
        }
        fd = open(argv[1], O_RDONLY);
        if (fd == -1)
        {
                perror(NULL);
                return (1);
        }
        bytesread = read(fd, buffer, 10);
        while (bytesread)
        {
                printf("%s", buffer);
                bytesread = read(fd, buffer, 10);
        }
        close(fd);
        return (0);
}
