#include "md5.h"
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <bits/stdc++.h> 
#include <signal.h>


const char* string;
void check(int sig){
    if (strlen(string) == 32 ){
        exit(0);
    }
}

int main (){
    int p;
    signal(SIGINT,check);
    int fd1[2];
    int fd2[2];
    if (pipe(fd1)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
    if (pipe(fd2)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    }
    p = fork(); 
    
    if (p < 0) 
    { 
        fprintf(stderr, "fork Failed" ); 
        return 1; 
    } 
    else if (p > 0)  
    {
        char buf[20];
        printf("plain text:");
        scanf("%s", buf); 
        char md[33];
        close(fd1[0]);
        write(fd1[1], buf, strlen(buf)+1); 
        close(fd1[1]); 
        wait(NULL); 
        sleep(1);
        close(fd2[1]);
        read(fd2[0], md, 33);
        printf("encrypted by process %d : %s\n" ,p, md); 
        kill(p,SIGKILL);
        close(fd2[0]);
    }
    else 
    {
        close(fd1[1]);
        char con[20];
        read(fd1[0], con, 20);
        string = md5(con).c_str();
        close(fd1[0]); 
        close(fd2[0]);
        write(fd2[1], string, strlen(string)+1); 
        close(fd2[1]);
        kill(getpid(), SIGINT);
    }
    exit(0);
}
