// Author: Utkarsh
// Reg.no: 20142027
// Objective: Block and unblock signal
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

void handler(int signal,siginfo_t * si,void * x){
    if(signal==SIGINT)
        printf("The Encountered signal is SIGINT \n");
    if(signal==SIGHUP)
        printf("The Encountered signal is SIGHUP \n");
    if(signal==SIGABRT)
        printf("The Encountered signal is SIGABRT \n");
}

void block_sig(int signal, sigset_t *set){
    sigaddset(set, signal);
}

void unblock_sig(int signal, sigset_t *set){
    sigdelset(set, signal);
}

int main(){
    struct sigaction handle;
    handle.sa_sigaction=handler;
    handle.sa_flags=SA_SIGINFO;

    sigaction(SIGINT,&handle,NULL);
    sigaction(SIGHUP,&handle,NULL);
    sigaction(SIGABRT,&handle,NULL);

    sigset_t sset;
    sigemptyset(&sset);
    printf("Enter the corresponding label to select choice:\n1.To Block SIGINT\n2.To Unblock SIGINT\n3.To Block SIGHUP\n4.To Unblock SIGHUP\n5.To Block SIGABRT\n6.To Unblock SIGABRT\n7.To Exit the program:\n");
    int flag = 0, choice;
    while(1){
        scanf("%d",&choice);
        if(sigprocmask(SIG_BLOCK,&sset,NULL) == -1){
            printf("Error while signal masking!!\n");
            exit(1);
        }

        switch(choice)
        {
            case 1: block_sig(SIGINT, &sset);break;
            case 2:unblock_sig(SIGINT, &sset);break;
            case 3:block_sig(SIGHUP, &sset);break;
            case 4:unblock_sig(SIGHUP, &sset);break;
            case 5:block_sig(SIGABRT, &sset);break; 
            case 6:unblock_sig(SIGABRT, &sset);break;
            case 7:sigprocmask(SIG_UNBLOCK,&sset,NULL);
                   exit(0);
        }
        printf("\nThe list of blocked signals is :\n");
        if(sigismember(&sset,SIGINT)){
            printf("%d. SIGINT\n",++flag);
        }
        if(sigismember(&sset,SIGHUP)){
            printf("%d. SIGHUP\n",++flag);
        }
        if(sigismember(&sset,SIGABRT)){
            printf("%d. SIGABRT\n",++flag);
        }
        if(!flag){
            printf("No signals are blocked\n");
        }
        flag = 0;
        printf("Enter your choice: ");
    }
}

