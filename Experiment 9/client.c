#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

int main(int argc, char **argv){

  int sockfd, connfd;
  char msg[100];
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in myaddr;
  myaddr.sin_family = AF_INET;
  myaddr.sin_port = htons(5100);
  myaddr.sin_addr.s_addr=htonl(INADDR_ANY);

  if(connect(sockfd, &myaddr, sizeof(myaddr))!=-1){
    bzero(msg, sizeof(msg));
    printf("Connection established\n");
    printf("Enter the message: ");
    scanf("%[^\n]%*c", msg);
    write(sockfd, msg, 100);
    printf("Message send\n");
    bzero(msg, sizeof(msg));
    read(sockfd, msg, sizeof(msg));
    printf("From Server : %s", msg);
    close(sockfd);
  }else{
    printf("Error binding connecting\n");
  }
}
