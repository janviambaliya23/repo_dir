#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 9090
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    while (1) {
        printf("Enter message: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // Send message
        sendto(sockfd, buffer, strlen(buffer), 0,
               (struct sockaddr *)&server_addr, sizeof(server_addr));

        // Receive reply
        recvfrom(sockfd, buffer, BUFFER_SIZE, 0, NULL, NULL);

        printf("Server: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}
