#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

int main(int argc, char **argv){

  int sockfd, connfd;
  int mpid;
  char input[100];
  char msg[500], username[100];
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in myaddr;
  myaddr.sin_family = AF_INET;
  myaddr.sin_port = htons(5100);
  myaddr.sin_addr.s_addr=htonl(INADDR_ANY);
  printf("Enter Username: ");
  scanf("%s", username);

  if(connect(sockfd, (struct sockaddr *)&myaddr, sizeof(myaddr))!=-1){
    bzero(msg, sizeof(msg));
    printf("Connection established\n");
    mpid = fork();
    if(mpid==0){
      while(1){
        printf("Enter the message: ");
        scanf("%s", input);
        strcat(msg, username);
        strcat(msg, ":");
        strcat(msg, input);
        send(sockfd, msg, sizeof(msg), 0);
        printf("Message sent\n");
        bzero(msg, sizeof(msg));
      }
      close(sockfd);
    }else{
      // execl("/usr/bin/xterm", "xterm", "-e", "client.out", NULL);
      while(recv(sockfd, msg, sizeof(msg), 0)){
        printf("%s\n", msg);
      }

    }
  }else{
    printf("Error in connecting\n");
  }
}
