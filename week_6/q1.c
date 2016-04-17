//Author: Utkarsh
//Reg.no: 20142027
//Objective: Associate action for SIGCHLD using sigaction
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/wait.h>
/*
siginfo_t {
    pid_t    si_pid;       Sending process ID
    int      si_status;    Exit value or signal
    sigval_t si_value;     Signal value
}
*/
//If SA_SIGINFO flag is given to sigaction, we can use above structure to get more info
// Reference: MAN PAGE sigaction, {91,124}
void child_term(int sig,siginfo_t *child,void *x){
    printf("This is signal handler\n");
    if(child->si_code == CLD_EXITED)
        printf("Child with %d pid exited with %d status \n",child->si_pid, child->si_status);
}
struct sigaction handler;

int main(){
    int exit_status;
    handler.sa_sigaction=child_term;
    handler.sa_flags=SA_SIGINFO; 
    sigaction(SIGCHLD,&handler,NULL);

    pid_t pid=fork();

    if(pid==-1){
        pid = fork();
        if(pid == -1){
            printf("Error while forking!!\n");
        }
    }
    if(pid==0){
        printf("This is child with pid %d, enter the exit status: ",getpid());
        scanf("%d",&exit_status);
        exit(exit_status);
    }
    else{
        wait(&exit_status);
        printf("Child exited successfully\n");
    }
    return 0;
}

