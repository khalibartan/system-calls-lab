//Author: Utkarsh
//Reg.no : 20142027
//Objective: Display man page of give command line argument on a new xterm
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(int argc,char *argv[]){
    int exit_status, fd[2];
    if(pipe(fd) == -1){
        printf("Error while creating pipes, exiting");
        return 1 ;
    }
    pid_t pid = fork();
    if(pid == -1){
        printf("Error while forking, trying to create new child process");
        pid = fork();
    }
    if(pid == 0){
        close(fd[1]);
        dup2(fd[0],STDIN_FILENO);
        char buff[100];
        char buff2[100]="man ";
        scanf("%s",buff);
        printf("This is child process with process id %d, will open a new terminal with man of %s\n",getpid(),buff);
        strcat(buff2, buff); // creating string "man <arg>"
        char *args[] = {"xterm","-e",buff2,NULL};
        execvp(args[0],args);
    }
     else{
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);
        printf("%s",argv[1]);
    }
    return 0;
}
