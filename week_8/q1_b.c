#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
long balance = 1000000;
long withdraw = 600000;
long deposit = 500000;

void *withdraw_func(void *val)
{
        long wd = (long)val;
        balance = balance - wd;
        pthread_exit(NULL);
}
void *deposit_func(void *val)
{
        long dd = (long)val;
        balance = balance + dd;
        pthread_exit(NULL);
}
long main()
{
        pthread_t thread_wd, thread_dep;
        
        pthread_create(&thread_wd,NULL,withdraw_func,(void *)withdraw);
        pthread_create(&thread_dep,NULL,deposit_func,(void *)deposit);
        pthread_join(thread_dep,NULL);
        printf("The total balance is %ld\n",balance);        
        return 0;
}
