#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
    int exit_status;
    pid_t pid;
    while(1){
        pid = fork();
        if(pid == -1){
            continue;
        }
        else if(pid == 0){
            printf("Child process with process id %d and parent process id %d\nEnter the exit status ( <= 255): ",getpid(),getppid());
            scanf("%d",&exit_status);
           if(exit_status > 255){
                printf("Exit status > 255 are not supported, will now exit with status 1\n");
                exit_status = 1;
            }
            sleep(1);
            printf("Exited\n");
            exit(exit_status); // Parent process after wait will not run
        }
        else{
            printf("I'm parent process with process id %d\n",getpid());
            pid = wait(&exit_status);
            if(WIFEXITED(exit_status)){
                printf("Sucessfuly exited the child with process id  %d and with exit status %d\n",pid, WEXITSTATUS(exit_status));
                break;
            }
            else if(WIFSIGNALED(exit_status)){
                printf("Child was killed by signal %d\n",WTERMSIG(exit_status));
                break;
            }
            else if(WCOREDUMP(exit_status)){
                printf("Core was dumped");
                break;
            }
        }
    }
    return 0;
}
