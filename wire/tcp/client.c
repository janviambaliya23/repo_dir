// client.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 2000

int main() {
    int sock;
    struct sockaddr_in serv_addr;
    char message[1024];

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Connect to localhost
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    printf("Connected to server!\n");

    // Send loop (ONLY send)
    while (1) {
        printf("Enter message: ");
        fgets(message, sizeof(message), stdin);

        send(sock, message, strlen(message), 0);
    }

    close(sock);
    return 0;
}
