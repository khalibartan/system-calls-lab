//Author: Utkarsh (khalibartan)
//reg.no : 20142027
//Objective: Take a message from parent and display it through child
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>

int main(){
    int fd[2];
    if(pipe(fd) == -1){
        exit(1); // Error happened Exit
    }; // Creating a pipe
    char buff1[100],buff2[100];
    pid_t pid = fork();

    if(pid == -1){
        write(1,"Got error while forking, creating a new child\n",sizeof(char)*47);
        pid = fork();
        if(pid == -1){
            printf("Error happened Exiting!..");
            exit(1);
        }
    }

    if(pid == 0){
        close(fd[1]); // Closing writing end of pipe
        read(fd[0],buff2,sizeof(char)*100); //Reading message
        int len = strlen(buff2);
        printf("This is child process with process id %d, used pipe to receive a message from parent\n",getpid());
        write(1,buff2,sizeof(char)*len);
    }
    else{
        close(fd[0]); // Closing the read end of pipe
        write(1,"Parent will send a message to child\nType a message to send: ",sizeof(char)*60);
        scanf("%s",buff1);
        write(fd[1],buff1,sizeof(char)*strlen(buff1)); // Writing message
    }
    return 0;
}
