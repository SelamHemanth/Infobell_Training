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

int hexa_char_To_int(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    else if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    else if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    else
        return -1;
}

void hex_to_binary(const char *hexString, char *binaryString)
{
    int i, j = 0;
    for (i = 0; hexString[i] != '\0'; ++i)
    {
        int val = hexa_char_to_int(hexString[i]);
        binaryString[j++] = (val & 8) ? '1' : '0';
        binaryString[j++] = (val & 4) ? '1' : '0';
        binaryString[j++] = (val & 2) ? '1' : '0';
        binaryString[j++] = (val & 1) ? '1' : '0';
    }
    binaryString[j] = '\0';
}

int main() 
{
    int msqid;
    key_t key;
    struct msg_buffer message;

    key = ftok("/tmp", 'A');
    if (key == -1)
    {
        perror("ftok is failed");
        exit(1);
    }

    msqid = msgget(key, 0666 | IPC_CREAT);
    if (msqid == -1)
    {
        perror("msgget is failed");
        exit(1);
    }

    printf("waiting for messages...\n");

    while (1) 
    {
        if (msgrcv(msqid, &message, sizeof(message.mtext), 1, 0) == -1)
       	{
            perror("msgrcv is failed");
            exit(1);
        }
        printf("received hex value: %s\n",message.mtext);
        char binary_string[33];
        hexa_to_binary(message.mtext, binary_string);
        printf("sending binary: %s\n",binary_string);
        strcpy(message.mtext, binary_string);
        message.mtype = 2;
        if (msgsnd(msqid, &message, sizeof(message.mtext), 0) == -1)
       	{
            perror("msgsnd is failed");
            exit(1);
        }
    }

    return 0;
}

