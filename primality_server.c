#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include<stdbool.h>
#include <math.h>


bool is_prime(int n)
{
 if (n<2)
   return false;
 for(int i=2;i<=sqrt(n);i++)
 {
  if (n%i==0)
  {
   return false;
  }
 }
 return true;
}
int main() {

    int sockfd, newsock;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);
    char buffer[1024],response[1024];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));
    listen(sockfd, 5);
    printf("Waiting for connection...\n");

    newsock = accept(sockfd, (struct sockaddr *)&client, &len);
    /*read(newsock, buffer, sizeof(buffer));
    printf("Message: %s \n", buffer);
    read(newsock, buffer, sizeof(buffer));
    printf("%s",buffer);*/
    int bytes_received = read(newsock, buffer, sizeof(buffer) - 1);
    buffer[bytes_received] = '\0'; // Null-terminate string
    printf("Message: %s\n", buffer);

    bytes_received = read(newsock, buffer, sizeof(buffer) - 1);
    buffer[bytes_received] = '\0'; // Null-terminate again
    printf("Received number: %s\n", buffer);
    
    int n=atoi(buffer);
    if (is_prime(n))
    
       strcpy(response,"it is a prime number\n");
    
    else
        strcpy(response,"it is not a prime number\n");
    

    send(newsock, response, strlen(response), 0);
    close(newsock);
    close(sockfd);

    return 0;
}

