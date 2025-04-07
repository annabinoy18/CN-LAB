#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<time.h>

int main()
{
 int sockfd;
 char buffer[1024];
 struct sockaddr_in server,client;
 socklen_t len=sizeof(client);
 
 sockfd=socket(AF_INET,SOCK_DGRAM,0);
 
 server.sin_family=AF_INET;
 server.sin_port=htons(8080);
 server.sin_addr.s_addr=INADDR_ANY;
 
 bind(sockfd,(struct sockaddr*)&server,sizeof(server));
 
 printf("server is ready\n");
 
 recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&client,&len);
 printf("the msg is %s\n",buffer);
 
 time_t currentime=time(NULL);
 char* strtime=ctime(&currentime);

 
 sendto(sockfd,strtime,strlen(strtime),0,(struct sockaddr *)&client,len);
 
 close(sockfd);
 
 return 0;
}
