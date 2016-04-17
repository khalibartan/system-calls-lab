// Author: Utkarsh
// Reg.no: 20142027
// Objective: Multipurpose signal handler
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void handler(int signal,siginfo_t * si,void * x)
{
    switch(signal){
        case SIGINT:
            printf("Caught signal is SIGINT \n");
            break;
        case SIGHUP:
            printf("Caught signal is SIGHUP \n");
            break;
        case SIGTERM:
            printf("Caught signal is SIGTERM\n");
    }
    sleep(2);
    printf("Exiting signal handler\n");
}

int main()
{
    pid_t pid=fork();
    struct sigaction handle;

    //Creating signal mask
    sigset_t sset;
    sigemptyset(&sset);
    sigaddset(&sset,SIGINT);
    sigaddset(&sset,SIGHUP);
    sigaddset(&sset,SIGTERM);

    handle.sa_sigaction=handler;
    handle.sa_flags=SA_SIGINFO;
    handle.sa_mask=sset;

    sigaction(SIGINT,&handle,NULL);
    sigaction(SIGHUP,&handle,NULL);
    sigaction(SIGTERM,&handle,NULL);

    if(pid == -1){
        pid = fork();
        if(pid == -1){
            printf("Error while forking!!\n");
        }
    }
    if(pid){
        printf("Sending Signal SIGINT\n");
        sleep(1);
        kill(pid,SIGINT);
        printf("Sending Signal SIGHUP\n");
        sleep(1);
        kill(pid,SIGHUP);
        printf("Sending Signal SIGTERM\n");
        sleep(1);
        kill(pid,SIGTERM);
        sleep(4);
        printf("Sending Signal SIGKILL\n");
        kill(pid,SIGKILL);
    }
    else{
        while(1);
    }
    return 0;
}
