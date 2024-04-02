#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
    int fd;
    ssize_t Read;
    char buf[256];

    printf("Creating named pipe: %s\n","./mypipe");
    if (mkfifo("./mypipe", 0666) == -1)
    {
        perror("mkfifo is failed");
        exit(1);
    }

    printf("Opening named pipe for reading: %s\n", "./mypipe");
    fd = open("./mypipe", O_RDONLY);
    if (fd == -1) 
    {
        perror("open is failed");
        exit(1);
    }

    printf("Reading from named pipe...\n");
    while ((Read = read(fd, buf, sizeof(buf))) > 0) 
    {
        buf[Read] = '\0';
        printf("Received %ld bytes from named pipe: %s\n", (long)Read, buf);
        if (strcmp(buf, "exit\n") == 0) 
	{
            printf("Received 'exit' command. Exiting.\n");
            break;
        }
    }

    close(fd);
    unlink("./mypipe");
    return 0;
}

