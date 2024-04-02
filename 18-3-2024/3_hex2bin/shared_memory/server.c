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
    char buffer[SHM_SIZE];

    key = ftok("/tmp", 'A');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    shmid = shmget(key, sizeof(struct shared_memory), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    shm = (struct shared_memory *)shmat(shmid, NULL, 0);
    if (shm == (void *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    printf("[+] Server[%d]: waiting for messages...\n", getpid());

    while (1) {
        while (shm->written == 0)
            usleep(100000); // Sleep for 100ms

        printf("[+] Server[%d]: received hex value: %s\n", getpid(), shm->message);

        // Convert hexadecimal to binary
        unsigned long hex_val = strtoul(shm->message, NULL, 16);
        char binary_string[33];
        snprintf(binary_string, sizeof(binary_string), "%32lx", hex_val);

        printf("[+] Server[%d]: sending binary: %s\n", getpid(), binary_string);

        // Write binary string back to shared memory
        strcpy(buffer, binary_string);
        strncpy(shm->message, buffer, SHM_SIZE);
        shm->written = 0;
    }

    return EXIT_SUCCESS;
}

