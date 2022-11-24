#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/wait.h>
#include<unistd.h>
#include<time.h>
struct timespec drake1;
struct timespec drake2;

int main(){
  pid_t snoop[3];
  int dababy=3;
  char *arr[]={"./bash1.sh","./bash2.sh","./bash3.sh"};

  for(int i=0;i<dababy;i++){
    clock_getime(CLOCK_MONOTONIC,&drake1);
    pid_t x=fork();
    if(x<0){
      perror("fork");
      exit(0);
    }
    else if(x==0){
      execlp(arr[i],NULL);
      exit(0);
    }
    else{
      snoop[i]=x;
    }
  }
  pid_t carti;
  while(dababy>0){
    carti=wait(NULL);
    clock_getime(CLOCK_MONOTONIC,&drake2);
    //printf("Child with PID %ld",(long)carti);
    if(carti==snoop[dababy]){
      printf("%d\n",dababy);
      }
    --dababy;
  }
  printf("%lf seconds \n", (double)(drake2.tv_sec-drake1.tv_sec) + ((double)(drake2.tv_nsec-drake1.tv_nsec)/1000000000L));
}