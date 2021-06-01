#include<stdio.h>
#include <unistd.h>
void main(){
  int dimension = 3;
  int mtrx1[3][3] = {{1, 2, 3}, {3, 4, 5}, {6, 7, 9}};
  int mtrx2[3][3] = {{1, 2, 3}, {3, 4, 5}, {6, 7, 9}};
  int pid;
  pid = fork();
  if(pid < 0){
    printf("Unable to create child process\n");
  }
  else if(pid==0){
    printf("\n\nSum in child process \n");
    for(int i=0; i<dimension; i++){
      printf("\n");
      for(int j=0; j<dimension; j++){
        printf("%d\t", mtrx1[i][j] + mtrx2[i][j]);
      }
    }
  }else{
    printf("Product of matrices \n");
    int temp=0;
    for(int i=0; i<dimension; i++){
      printf("\n");
      for(int j=0; j<dimension; j++){
        temp = 0;
        for(int k=0; k<dimension; k++){
          temp += mtrx1[i][k] * mtrx2[k][j];
        }
        printf("%d\t", temp);
      }
    }
  }
}
