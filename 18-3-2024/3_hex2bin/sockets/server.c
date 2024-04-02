#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>

#define MAX_MESSAGE_SIZE 256
#define PORT 8080

int main(int argc, char *argv[]) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[MAX_MESSAGE_SIZE] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                       (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    int valread;
    while ((valread = read( new_socket , buffer, MAX_MESSAGE_SIZE)) > 0) {
        printf("[+] Server[%d]: received hex value: %s\n", getpid(), buffer);

        // Convert hexadecimal to binary
        unsigned long hex_val = strtoul(buffer, NULL, 16);
        char binary_string[33];
        snprintf(binary_string, sizeof(binary_string), "%32lx", hex_val);

        printf("[+] Server[%d]: sending binary: %s\n", getpid(), binary_string);

        // Send binary string back to client
        send(new_socket , binary_string , strlen(binary_string) , 0 );
        printf("[+] Server[%d]: binary value sent to client\n", getpid());
        memset(buffer, 0, sizeof(buffer));
    }
    return 0;
}

