// Author : Utkarsh (Khalibartan)
// reg.no : 20142027
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
int counter=0;
void SIGhandler(int sig)
{
    signal(sig,SIG_IGN);
    if(counter==5){
        printf("SIGALRM signal generated for 5 times\nexiting....\n");
        exit(0);
    }
    printf("ALARM signal generated.. this is counter %d\n",counter+1);
    counter++;
    alarm(2);
    signal(SIGALRM,SIGhandler);
}
int main()
{   int time;
    printf("Enter the alarm time to set: ");
    scanf("%d",&time);
    printf("This program will send an alarm signal after %d seconds,\nand will then genrate 5 alarm signals one after another\n",time);
    alarm(time);
    signal(SIGALRM,SIGhandler);
    while(1){
        pause();
    }
    return 0;
}
