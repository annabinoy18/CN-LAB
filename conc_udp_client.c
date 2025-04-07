#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
int main()
{
int sockfd;
char buffer[1024]="Requesting the time now\n";
char response[1024];
struct sockaddr_in server;
socklen_t len=sizeof(server);

sockfd=socket(AF_INET,SOCK_DGRAM,0);

server.sin_family=AF_INET;
server.sin_port=htons(8080);
server.sin_addr.s_addr=inet_addr("127.0.0.1");

sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&server,len);
printf("message sent\n");

recvfrom(sockfd,response,sizeof(response),0,(struct sockaddr *)&server,&len);
printf("Time received %s\n",response);

close(sockfd);

return 0;
}
