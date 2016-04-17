// Author: Utkarsh (Khalibartan)
// reg.no: 20142027
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
int status;
void SIGhandler(int sig)
{
    printf("SIGCHILD signal generated, child exited with %d exit status\n",WEXITSTATUS(status));
}
int main()
{
    pid_t pid = fork();
    if(pid<0){
        pid = fork();
        if(pid<0){
            printf("Error while forking.. exiting!!");
            exit(1);
        }
    }
    if(pid==0)
    {
        printf("This is child process, enter the exit status of child: ");
        scanf("%d",&status);
        sleep(1);
        exit(status);
    }
    else
    {
        signal(SIGCHLD,SIGhandler);
        wait(&status);
    }
    return 0;
}
