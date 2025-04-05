#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd, newsock;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);
    char buffer[1024];

    // 1. Create a TCP socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // 2. Setup server address structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY; // Listen on all interfaces
    server.sin_port = htons(8080); // Port number in network byte order

    // 3. Bind socket to the specified IP and port
    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Bind failed");
        exit(1);
    }

    // 4. Listen for incoming connections
    listen(sockfd, 5);
    printf("Waiting for connection...\n");

    // 5. Accept a connection from client
    newsock = accept(sockfd, (struct sockaddr *)&client, &len);
    if (newsock < 0) {
        perror("Accept failed");
        exit(1);
    }

    // 6. Receive message from client
    memset(buffer, 0, sizeof(buffer)); // Clear the buffer
    recv(newsock, buffer, sizeof(buffer), 0); // safer than read()

    // 7. Print the message
    printf("Message: %s\n", buffer);

    // 8. Send a response to the client
    send(newsock, "Hello from server", strlen("Hello from server"), 0);

    // 9. Close both sockets
    close(newsock);
    close(sockfd);

    return 0;
}
