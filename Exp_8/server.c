#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>

# define MAXLINE 1024

int main(int argc, char **argv){

  int sockfd;
  char msg[100];
  char buffer[MAXLINE];
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  struct sockaddr_in myaddr;
  myaddr.sin_family = AF_INET;
  myaddr.sin_port = htons(5100);
  myaddr.sin_addr.s_addr=htonl(INADDR_ANY);

  int len = sizeof(myaddr);
  if(bind(sockfd, (struct sockaddr*)&myaddr, sizeof(myaddr))!=-1){
    bzero(msg, sizeof(msg));
    recvfrom(sockfd, msg, sizeof(msg), 0, (struct sockaddr *)&myaddr, sizeof(myaddr));
    printf("MESSAGE FROM CLIENT: %s\n", msg);
    bzero(msg, sizeof(msg));
    strcpy(buffer, "RECEIVED");
    sendto(sockfd, (char *)buffer, MAXLINE, MSG_CONFIRM, (struct sockaddr *)&myaddr, sizeof(myaddr));
    printf("Program ended\n");
  }else{
    printf("Error binding socket\n");
  }
}
