//Objective: To demonstrate basic fork usage
//Author: Utkarsh (khalibartan)
// Reg no : 20142027
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
    int exit_val;
    int status;
    printf("This program will demonstrate basic fork usage and what wait does\nChild will sleep for 1 sec and pass a exit status\n");
    pid_t pid = fork();
    if(pid == -1){
        pid = fork(); // Error happend create a new child
    } 
    if (pid == 0) 
        {
            printf("CHILD: I am the child process, with process id %d and my parents id is %d\n",getpid(),getppid());
            printf("Enter the exit value: ");
            scanf("%d",&exit_val);
            sleep(1);
            printf("Exiting the child\n");
            exit(exit_val); // Parent part won't execute unless value received 
        }
        else 
        {
            printf("PARENT: I am the parent process! with process id %d\n",getpid());
            printf("PARENT: I will now wait for my child to exit.\n");
            wait(&status); 
            printf("PARENT: Child's exit code is: %d\n", WEXITSTATUS(status));
        }
        return 0;
    
}
