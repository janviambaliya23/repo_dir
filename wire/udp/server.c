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
    struct sockaddr_in server_addr, client_addr;
    socklen_t len;

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind
    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("UDP Server running on port %d...\n", PORT);

    while (1) {
        len = sizeof(client_addr);

	// Receive message
	int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0,
			(struct sockaddr *)&client_addr, &len);

	buffer[n] = '\0';   // ✅ correct null termination

	printf("Client: %s\n", buffer);


	// Send reply
	sendto(sockfd, "Message received", 16, 0,
			(struct sockaddr *)&client_addr, len);
    }

    close(sockfd);
    return 0;
}
