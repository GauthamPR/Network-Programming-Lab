#include<stdio.h>
#include<sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

struct msg_bfr{
  long type;
  char msg_txt[100];
}message;

int main(){
  key_t key = ftok("shared", 7777);
  int shmid = shmget(key, 1024, 0666|IPC_CREAT);
  char *str = (char *)shmat(shmid, NULL, 0);
  scanf("%s", str);
  shmdt(str);
  return 0;
}
