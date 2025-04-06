#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define TIMEOUT 3
#define PORT 8080
#define BUFFERSIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFERSIZE] = {0};
    char filename[BUFFERSIZE] = {0};

    int bytes_recv = recv(client_socket, filename, BUFFERSIZE, 0);
    if (bytes_recv < 0) {
        perror("Error in receiving filename");
        close(client_socket);
        return;
    }

    FILE *file = fopen(filename, "r");  
    if (file == NULL) {
        char *errormsg = "File not found";
        send(client_socket, errormsg, strlen(errormsg), 0);
        perror("File not found");
    } else {
        while (fgets(buffer, BUFFERSIZE, file) != NULL) {
            send(client_socket, buffer, strlen(buffer), 0);
            memset(buffer, 0, BUFFERSIZE);
        }
        printf("File sent to client\n");
        fclose(file); 
    }

    close(client_socket);
}

int main() {
    int client_socket, server_socket;
    struct sockaddr_in client_addr, server_addr;
    socklen_t addrlen = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addrlen);
        if (client_socket < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }
        printf("Client connected\n");
        handle_client(client_socket);
    }

    close(server_socket);
    return 0;
}
