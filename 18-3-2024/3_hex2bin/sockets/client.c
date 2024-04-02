#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_MESSAGE_SIZE 256
#define PORT 8080

int main(int argc, char *argv[]) {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[MAX_MESSAGE_SIZE] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connection failed");
        exit(EXIT_FAILURE);
    }

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <hexadecimal_number>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("[+] Client[%d]: connecting to the server process... OK\n", getpid());

    // Send hex value to server
    send(sock , argv[1] , strlen(argv[1]) , 0 );
    printf("[+] Client[%d]: sending hex value %s\n", getpid(), argv[1]);

    // Receive binary value from server
    valread = read( sock , buffer, MAX_MESSAGE_SIZE);
    printf("[+] Client[%d]: received binary: %s\n", getpid(), buffer);
    return 0;
}

