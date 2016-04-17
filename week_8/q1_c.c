#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
long balance = 1000000;
long withdraw1 = 600000;
long deposit = 500000;
pthread_mutex_t lock;
void *withdraw_func(void *val)
{
        pthread_mutex_lock(&lock);
        long wd = (long)val;
        printf("balance before withdrawing %ld is %ld\n",wd,balance);
        sleep(1); 
        balance = balance - wd;
        printf("balance after withdrawing %ld is %ld\n",wd,balance); 
        pthread_mutex_unlock(&lock);        
        pthread_exit(NULL);
}
void *deposit_func(void *val)
{
        pthread_mutex_lock(&lock);
        long dep = (long)val;
        printf("balance before depositing %ld is %ld\n",dep,balance);
        sleep(1);
        balance = balance + dep;
        printf("balance after depositing %ld is %ld\n",dep,balance); 
        pthread_mutex_unlock(&lock);        
        pthread_exit(NULL);
}
long main()
{
        pthread_mutex_init(&lock,NULL);
        pthread_t thread_wd, thread_dep;
        pthread_create(&thread_wd,NULL,withdraw_func,(void *)withdraw1);
        pthread_create(&thread_dep,NULL,deposit_func,(void *)deposit);
        pthread_join(thread_wd,NULL);
        pthread_join(thread_dep,NULL);
        printf("The total balance is %ld\n",balance);  
        pthread_mutex_destroy(&lock);      
        return 0;
}
