#include <signal.h>
#include <stdio.h>

int cpid[5];
int k;

int sigCathcher(int sig){
    signal(SIGINT,sigCathcher);
  printf("PID %d caught one\n",getpid());
  if (k  > -1){
      kill(cpid[k],SIGINT);
  }
}

int main ()
{
    int zombie;
    int status;
    int pid;
    signal(SIGINT,sigCathcher);
    for (int i=0; i<5; i++)
    {
         if ((pid = fork()) == 0){
            printf("PID %d ready\n", getpid());
            k = i-1;
            pause();
            exit(0);
        }
        else {
            cpid[i] = pid;
        }
    }
    sleep(2);
    kill(cpid[4],SIGINT);
    sleep(2);
    for(int i=0;i<5;i++) 
    {
        zombie = wait(&status);
        printf("Process %d id dead\n",zombie);
    }
    exit(0);
}
