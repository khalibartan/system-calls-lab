//Author: Utkarsh(khalibartan)
//Reg.no: 20142027
//Objective: Using exact system call to run ls -l in child and then sorting result in parent
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<stdlib.h>

int main(){
    int exit_status=1,fd[2];
    if(pipe(fd) == -1){
        printf("Couldn't initialize pipe\n");
        return 1;
    }
    pid_t pid = fork();
    if(pid == -1){
        printf("Error while forking, trying to create a new child process\n");
        pid = fork();
    }
    if(pid == 0){
        close(STDOUT_FILENO);
        dup(fd[1]); //Since STDOUT_FILENO is smallest fd[1] will be assigned to it
        close(fd[0]);
        char *args[]={"ls","-l",NULL};
        execvp(args[0],args); //Output instead of displaying on STDOUT will be written in pipe
    }
    else{
         // No need for wait system call, pipe will do this
          close(STDIN_FILENO); // Same as above
          dup(fd[0]);
          close(fd[1]);
          char *args[] = {"sort",0};
          //execv("/bin/sort",args); // Displayed on system
          execlp("sort","sort",NULL); // Not Using execv because on my system sort file wasn't present in /bin
          // execlp and execvp searches for path of the file
    }
    return 0;
}
