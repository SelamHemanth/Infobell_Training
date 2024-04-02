#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_MESSAGE_SIZE 256

struct msg_buffer
{
    long mtype;
    char mtext[MAX_MESSAGE_SIZE];
};

int main(int argc, char *argv[])
{
    int msqid;
    key_t key;
    struct msg_buffer message;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <hexadecimal_number>\n", argv[0]);
        exit(1);
    }

    key = ftok("/tmp", 'A');
    if (key == -1)
    {
        perror("ftok is failed");
        exit(1);
    }
    msqid = msgget(key, 0666);
    if (msqid == -1) 
    {
        perror("msgget is failed");
        exit(1);
    }

    printf("connecting to the server process... OK\n");
    strcpy(message.mtext, argv[1]);
    message.mtype = 1;
    if (msgsnd(msqid, &message, sizeof(message.mtext), 0) == -1)
    {
        perror("msgsnd is failed");
        exit(1);
    }

    printf("sending hex value %s\n", argv[1]);
    if (msgrcv(msqid, &message, sizeof(message.mtext), 2, 0) == -1)
    {
        perror("msgrcv is failed");
        exit(1);
    }
    printf("received binary: %s\n",message.mtext);

    return 0;
}

