//Objective: To create a chain of processes using fork
//Author : Utkarsh (khalibartan)
//Reg.no : 20142027
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>

int main(){
    printf("This program will create a chain of 5 processes\nRepresentation : parent's id --> self id\n");
    int i;
    pid_t pid;
    printf("Head process's process id id %d\n",getpid());
    for(i=0;i<4;i++){
        pid = fork();
        if(pid == -1){
            i--;
            continue; // Error occured , so decrease a loop counter
        }
        else if(pid){
            break; // Parent process with successfully created child, terminate it as will create new child
        }
        printf("%d --> %d\n",getppid(),getpid()); // Chain repr
    }
    return 0;
}
