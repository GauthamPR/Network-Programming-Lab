#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char **argv){

  int sockfd, connfd, n;
  char msg[500];
  char *token;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in myaddr;
  myaddr.sin_family = AF_INET;
  myaddr.sin_port = htons(5100);
  myaddr.sin_addr.s_addr=htonl(INADDR_ANY);

  int len = sizeof(myaddr);
  int pid;
  if(bind(sockfd, (struct sockaddr*)&myaddr, sizeof(myaddr))!=-1){
    if((listen(sockfd, 5))==0){
      while(connfd = accept(sockfd, (struct sockaddr*)&myaddr, &len)){
        pid = fork();
        if(pid==0){
          if(connfd==-1){
            perror("Accept");
            printf(": %s", strerror(errno));
          }else{
            bzero(msg, sizeof(msg));
            while(n = recv(connfd, msg, sizeof(msg), 0)){
              token = strtok(msg, ":");
              printf("MESSAGE FROM %s:", token);
              token = strtok(NULL, ":");
              printf("%s\n", token);
              bzero(msg, sizeof(msg));
              strcpy(msg, "RECEIVED");
              send(connfd, msg, sizeof(msg), 0);
            }
        }
        }
      }
      printf("Error accepting");
    }else{
      printf("Error listening socket\n");
    }
  }else{
    printf("Error binding socket\n");
  }
}
