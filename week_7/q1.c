// Author: Utkarsh
// Reg no: 20142027
#include<stdio.h>
#include<pthread.h>

void *PrintThread(void *thread_id){
    int i = 0;
    for(;i<5;i++){
        printf("Hello World , thread id : %d\n",thread_id);
    }
    pthread_exit(NULL);
}

int main(){
    pthread_t threads[10];
    int error_code;
    long id = 0;
    for(;id<10;id++){
        error_code = pthread_create(&threads[id],NULL,PrintThread, (void *)id);
        printf("%d\n",threads[id]);
        if(error_code){
            printf("Error, happened!!.. code returned is %d\n",error_code);
            return 1;
        }
    }
    pthread_exit(NULL);
    return 0;
}
