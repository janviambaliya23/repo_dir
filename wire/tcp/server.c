// server.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 2000

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024];

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Setup address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    // Listen
    listen(server_fd, 3);
    printf("Server listening on port %d...\n", PORT);

    // Accept connection
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    printf("Client connected!\n");

    // Receive loop (ONLY receive)
    while (1) {
        memset(buffer, 0, sizeof(buffer));

        int valread = read(new_socket, buffer, sizeof(buffer));
        if (valread <= 0) {
            printf("Client disconnected.\n");
            break;
        }

        printf("Client says: %s", buffer);
    }

    close(new_socket);
    close(server_fd);
    return 0;
}
