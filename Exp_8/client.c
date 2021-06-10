#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAXLINE 1024

int main(int argc, char **argv){

  int sockfd, connfd;
  char msg[100];
  char buffer[MAXLINE];
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  struct sockaddr_in myaddr;
  myaddr.sin_family = AF_INET;
  myaddr.sin_port = htons(5100);
  myaddr.sin_addr.s_addr=htonl(INADDR_ANY);

  bzero(msg, sizeof(msg));
  printf("Enter the message: ");
  scanf("%[^\n]%*c", msg);
  sendto(sockfd, msg, sizeof(msg), MSG_CONFIRM, (struct sockaddr *)&myaddr, sizeof(myaddr));
  printf("Message send\n");
  bzero(msg, sizeof(msg));
  recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)&myaddr, sizeof(myaddr));
  printf("FROM SERVER: %s", msg);
  printf("END\n");
  close(sockfd);
}
