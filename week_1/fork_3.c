//Objective : To create a tree of processes using fork
//Author : Utkarsh(khalibartan)
//Reg.no : 20142027

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(){
    printf("This program will create a tree of 8 processes in three levels\n");
    int i;
    pid_t pid, pid_1;
    for(i=0;i<3;i++){
        pid = fork();
        if(pid == -1){
            i--;
            continue;
        }
        if(pid == 0){
            printf("Child process with process id %d and parent process id %d\n",getpid(),getppid());
        }
        else{
            printf("Parent process with process id %d\n",getpid());
        }
    }
    return 0;
}
