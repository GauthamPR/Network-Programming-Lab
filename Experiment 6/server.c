#include<stdio.h>
#include<sys/msg.h>
#include <sys/ipc.h>

struct msg_bfr{
  long type;
  char txt[100];
}message;

int main(){
  key_t key = ftok("progfile", 65);
  int msgid = msgget(key, 0666|IPC_CREAT);
  msgrcv(msgid, &message, sizeof(message), 1, 0);
  int i = 0;
  printf("Received message: %s\n", message.txt);
  while(message.txt[i]!='\0'){
    message.txt[i] += 3;
    i++;
  }
  printf("Encrypted message: %s\n", message.txt);
  message.type = 2;
  msgsnd(msgid, &message, sizeof(message), 0);
  msgctl(msgid, IPC_RMID, NULL);
  return 0;
}
