#include<stdio.h>
#include<sys/msg.h>
#include <sys/ipc.h>
struct msg_bfr{
  long type;
  char txt[100];
}message;

int main(){
  key_t key = ftok("progfile", 65);
  int msgid = msgget(key, 0666 | IPC_CREAT);
  message.type = 1;
  printf("Enter the message: ");
  scanf("%s", message.txt);
  msgsnd(msgid, &message, sizeof(message), 0);
  msgrcv(msgid, &message, sizeof(message), 2, 0);
  printf("Received Encrypted message: %s\n", message.txt);
  msgctl(msgid, IPC_RMID, NULL);
  return 0;
}
