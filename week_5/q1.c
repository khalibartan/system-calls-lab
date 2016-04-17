// Author: Utkarsh (khalibartan)
// reg.no : 20142027
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

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
            printf("Termination (SIGTERM) signal given, ignoring...\n");
            break;
        default:
            signal(sig,SIG_DFL);
    }
    signal(sig,SIGhandler);     //Restoring the handler
}

int main()
{
    char buff[] = "This program will ignore SIGINT, SIGHUP, SIGTERM";
    write(1,buff,sizeof(char)*48);
    signal(SIGHUP, SIGhandler);
    signal(SIGINT, SIGhandler);
    signal(SIGTERM, SIGhandler);
    signal(SIGQUIT, SIGhandler);
    signal(SIGALRM, SIGhandler);
    signal(SIGSTOP, SIGhandler);
    while(1){
        pause();
    }
    return 0;
}
