//Author: Utkarsh(khalibartan)
//Reg.no: 20142027
//Objective : Similar to previous, but this time take command line arguments
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>

int main(int argc,char *argv[]){
    int exit_status=1,fd[2];
    if(pipe(fd)==-1){
        write(1,"Error in creating pipe exiting",sizeof(char)*30);
        exit(1);
    }
    pid_t pid = fork();
    if(pid == -1){
        printf("Error while forking , trying to create new process\n");
        pid = fork();
    }
    if(pid == 0){
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);
        execlp(argv[1],argv[1],argv[2],NULL);
       // exit(exit_status);
    }
    else{
        //No need for wait read side will automatically wait for completion of write
        //wait(&exit_status);
        //if(WIFEXITED(exit_status)){
            close(fd[1]);
            dup2(fd[0],STDIN_FILENO);
            //char *args[]={argv[3],NULL};
            execlp(argv[3],argv[3],NULL);
        //}
        //else{
        //    printf("Child couldn't exit , re run the program\n");
        //    exit(1);
        //}
    }
    return 0;
}
