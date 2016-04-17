//Author : Utkarsh (khalibartan)
//reg.no : 20142027
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>

void SIGhandler(int sig)
{
    switch(sig)
    {
        case SIGHUP:
            signal(sig,SIG_IGN);
            printf("Hung Up (SIGHUP) signal given, ignoring...\n");
            break;
        case SIGINT:
            signal(sig,SIG_IGN);
            printf("Interupt (SIGINT) type signal given, ignoring....\n");
            break;
        case SIGQUIT:
            printf("Quit signal (SIGQUIT) given, exiting....\n");
            exit(0);
        case SIGTERM:
            signal(sig,SIG_IGN);
            printf("Termination signal given, ignoring...\n");
            break;
        default:
            signal(sig,SIG_DFL);
    }
    signal(sig,SIGhandler);     //Restoring the handler
}
int main()
{
    pid_t pid;
    pid=fork();
    if(pid<0)
    {
        pid = fork();   // Try once again
        if(pid < 0){
            printf("Error in forking!..");
            exit(1); //error no zero exit status
        }
    }
    if(pid==0)
    {
        printf("THIS is child process\n");
        signal(SIGTERM,SIGhandler);
        signal(SIGHUP,SIGhandler);
        signal(SIGINT,SIGhandler);
        signal(SIGQUIT,SIGhandler);
        while(1){
            pause();
        }
        exit(0);
    }
    else if(pid>0)
    {
        printf(" This is parent process...\n Will generate signals for child in a moment..\n");
        sleep(2);
        printf("Sending SIGTERM signal to child\n\n");
        kill(pid,SIGTERM);
        sleep(3);
        printf("\nSending SIGHUP signal to child\n\n");
        kill(pid,SIGHUP);
        sleep(3);
        printf("\nSending SIGINT signal to child\n\n");
        kill(pid,SIGINT);
        sleep(3);
        printf("\nSending SIGQUIT signal to child\n\n");
        kill(pid,SIGQUIT);
    }
    return 0;
}
