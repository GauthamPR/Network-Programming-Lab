#include<stdio.h>
#include<sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int evaluate(char *);

int main(){
  key_t key = ftok("shmfile", 7777);
  int shmid = shmget(key, 1024, 0666|IPC_CREAT);
  char *str = (char *)shmat(shmid, NULL, 0);
  // printf("%s", str);
  int val = evaluate(str);
  printf("Value: %d", val);
  shmdt(str);
  shmctl(shmid, IPC_RMID, NULL);
  return 0;
}

int evaluate(char * expr){
  int x, y ,z;
  printf("Expression: %s\n", expr);
  sscanf(expr, "%d+%d+%d", &x, &y, &z);
  return (x+y+z);
}
