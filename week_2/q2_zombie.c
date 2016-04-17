#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
    int ex = 1;
    pid_t pid = fork();
    if(pid == -1){
        pid = fork();
    }
    if(pid == 0){
        printf("Pid: %d will remain as a zombie process\n",getpid());
        exit(-1);
    }
    else{
        sleep(25);
    }
    return 0;
}

