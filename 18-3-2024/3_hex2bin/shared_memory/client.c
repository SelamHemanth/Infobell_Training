#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

struct shared_memory {
    int written;
    char message[SHM_SIZE];
};

int main(int argc, char *argv[]) {
    int shmid;
    key_t key;
    struct shared_memory *shm;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <hexadecimal_number>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    key = ftok("/tmp", 'A');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    shmid = shmget(key, sizeof(struct shared_memory), 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    shm = (struct shared_memory *)shmat(shmid, NULL, 0);
    if (shm == (void *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    printf("[+] Client[%d]: connecting to the server process... OK\n", getpid());

    // Write hex value to shared memory
    strncpy(shm->message, argv[1], SHM_SIZE);
    shm->written = 1;

    printf("[+] Client[%d]: sending hex value %s\n", getpid(), argv[1]);

    while (shm->written == 1)
        usleep(100000); // Sleep for 100ms

    printf("[+] Client[%d]: received binary: %s\n", getpid(), shm->message);

    return EXIT_SUCCESS;
}

