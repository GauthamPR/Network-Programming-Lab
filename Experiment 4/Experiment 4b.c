#include<stdio.h>
#include <unistd.h>
int main(){
  int fd1[2], fd2[2];
  char pipeMsg1[20] = "From parent";
  char pipeMsg2[20] = "From child";
  char str1[20], str2[20];
  int status = pipe(fd1);
  if(status<0){
    printf("Call plumber");
  }
  status = pipe(fd2);

  if(status<0){
    printf("Call plumber");
  }
  int pid = fork();
  if(pid < 0){
    printf("Unable to create child process\n");
  }
  else if(pid==0){
    write(fd1[1], pipeMsg1, sizeof(pipeMsg1));
    read(fd2[0], str2, sizeof(str2));
    printf("%s%s\n", pipeMsg1, str2);
  }else{
    write(fd2[1], pipeMsg2, sizeof(pipeMsg1));
    read(fd1[0], str1, sizeof(str1));
    printf("%s%s\n", pipeMsg2, str1);
  }
  return 0;
}
