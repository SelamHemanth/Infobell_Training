#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/sysinfo.h>
#include <pthread.h>

#define BUFFER_SIZE 4096

typedef struct
{
    const char *src_file;
    const char *dest_dir;
    off_t start;
    off_t end;
} Thread_Args;

void * copyFile(void * arg) 
{
    Thread_Args* args = (Thread_Args*) arg;
    int src_fd, dest_fd;
    ssize_t bytes_read, bytes_written;
    char buffer[BUFFER_SIZE];

    if ((src_fd = open(args->src_file, O_RDONLY)) == -1)
    {
        perror("open system call failed");
        pthread_exit(0);
    }

    char dest_path[BUFFER_SIZE];
    snprintf(dest_path, sizeof(dest_path), "%s/%s", args->dest_dir, args->src_file);
    if ((dest_fd = open(dest_path, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) 
    {
        perror("open system call failed");
        close(src_fd);
        pthread_exit(0);
    }

    if (lseek(src_fd, args->start, SEEK_SET) == -1)
   {
        perror("lseek system call failed");
        close(src_fd);
        close(dest_fd);
        pthread_exit(0);
    }

    while ((bytes_read = pread(src_fd, buffer, BUFFER_SIZE, args->start)) > 0)
    {
        bytes_written = pwrite(dest_fd, buffer, bytes_read, args->start);
        if (bytes_written == -1)
       	{
            perror("pwrite system call failed");
            close(src_fd);
            close(dest_fd);
            pthread_exit(0);
        }
    }

    close(src_fd);
    close(dest_fd);
    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <source_file> <destination_directory>\n", argv[0]);
        return 1;
    }

    const char *src_file = argv[1];
    const char *dest_dir = argv[2];

    int cores = get_nprocs();
    printf("Number of CPU cores: %d\n", cores);
    struct stat st;
    if (stat(src_file, &st) == -1) 
    {
        perror("stat system call failed");
        return 1;
    }
    off_t file_size = st.st_size;
    off_t portion_size = file_size / cores;

    pthread_t threads[cores];
    Thread_Args thread_args[cores];

    for (int i = 0; i < cores; i++)
    {
        thread_args[i].src_file = src_file;
        thread_args[i].dest_dir = dest_dir;
        thread_args[i].start = i * portion_size;
        if(i == cores - 1)
	       thread_args[i].end =file_size;
	else
	      thread_args[i].end =(i + 1) * portion_size;
        pthread_create(&threads[i], NULL, copyFile, (void*)&thread_args[i]);
    }

    for (int i = 0; i < cores; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("File copied successfully.\n");

    return 0;
}

