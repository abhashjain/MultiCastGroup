#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#include "../includes/logger.h"

int main(int argc, char *argv[])
{
int listenfd = 0, connfd = 0;
struct sockaddr_in serv_addr; 

char sendBuff[1025];
char recvBuff[100];

int i = 0;

listenfd = socket(AF_INET, SOCK_STREAM, 0);
memset(&serv_addr, '0', sizeof(serv_addr));
memset(sendBuff, '0', sizeof(sendBuff)); 

serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
serv_addr.sin_port = htons(5000); 

bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

listen(listenfd, SOMAXCONN); 

connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 

do{  
  memset(recvBuff, '\0', sizeof(recvBuff));
  recv(connfd, recvBuff, sizeof(recvBuff),0);
  printf( "%s\n", recvBuff);
  memset(recvBuff, '\0', sizeof(recvBuff));
  sprintf(recvBuff, "Client got This is line %d", i);
  send(connfd, recvBuff, strlen(recvBuff), 0);
  
}while(++i<2); 

return 0;

} 
