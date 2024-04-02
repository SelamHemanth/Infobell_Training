#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
    int fd;
    ssize_t Write;
    char buf[256];

    if (argc < 2) 
    {
        fprintf(stderr, "Usage: %s [input_file]\n", argv[0]);
        exit(0);
    }
    const char *input_file ;
    if(argc > 1)
    {
	   input_file = argv[1] ;
    }
    else
    {
	  input_file = NULL;
    }
    printf("Opening input file: %s\n", (input_file != NULL) ? input_file : "stdin");
    FILE *file;
    if(input_file != NULL)
    {
	 file = fopen(input_file, "r") ;
    }
    else
    {
	  file = stdin;
    }
    if (file == NULL)
    {
        perror("fopen is failed");
        exit(0);
    }

    printf("Opening named pipe for writing: %s\n","./mypipe");
    fd = open("./mypipe", O_WRONLY);
    if (fd == -1) 
    {
        perror("open is failed");
        exit(0);
    }

    printf("Writing to named pipe...\n");
    while (fgets(buf, sizeof(buf), file) != NULL) 
    {
        Write = write(fd, buf, strlen(buf));
        if (Write == -1) {
            perror("write is failed");
            break;
        }
        printf("%ld bytes written to named pipe\n", (long)Write);
        if (strcmp(buf, "exit\n") == 0)
       	{
            printf("Sent 'exit' command. Exiting.\n");
            break;
        }
    }

    close(fd);
    fclose(file);
    return 0;
}

