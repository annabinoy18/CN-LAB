#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in server, client;
    char buffer[1024];
    socklen_t len = sizeof(client);

    // 1. Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 2. Server address configuration
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    // 3. Bind the socket to the server address
    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Waiting for data...\n");

    // 4. Receive data from client
    memset(buffer, 0, sizeof(buffer));
    recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client, &len);
    printf("Message from client: %s\n", buffer);

    // 5. Respond to client
    sendto(sockfd, "Hello from server", 18, 0, (struct sockaddr *)&client, len);

    // 6. Close socket
    close(sockfd);

    return 0;
}
