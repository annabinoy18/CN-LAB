#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in server;
    char buffer[1024] = "Hello Server";

    // 1. Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 2. Define server address
    server.sin_family = AF_INET;
    server.sin_port = htons(8080); // same as server port
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // localhost IP

    // 3. Connect to server
    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // 4. Send message to server
    send(sockfd, buffer, strlen(buffer), 0);

    // 5. Clear buffer and receive response
    memset(buffer, 0, sizeof(buffer));
    read(sockfd, buffer, sizeof(buffer));

    // 6. Print response from server
    printf("Response: %s\n", buffer);

    // 7. Close the socket
    close(sockfd);

    return 0;
}
