#include<stdio.h>
#include <unistd.h>
#include <string.h>

char * palindrome(char *);

void main(){
  int fd[2];
  int status = pipe(fd);
  char str[20];
  int pid = fork();
  if(pid < 0){
    printf("Unable to create child process\n");
  }
  else if(pid==0){
    printf("Child\n");
    char str2[20];
    read(fd[0],str2, sizeof(str2));
    printf("%s\n", palindrome(str2));
  }else{
    printf("Enter the string: ");
    scanf("%s", str);
    write(fd[1], str, sizeof(str));
    close(fd[1]);
  }
}


char * palindrome(char * str){
  char * msg = "It is a palindrome";
  char * err = "It is not a palindrome";
  char reversed[20];
  strcpy(reversed, str);
  int len = strlen(str);
  for(int i = 0; i<len; i++){
    reversed[i] = str[len-i-1];
  }
  if(strcmp(reversed, str)==0){
    return (msg);
  }else{
    return (err);
  }
}
