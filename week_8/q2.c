#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS  3
#define RACE_LIMIT 100

long race = 0;
pthread_mutex_t mutex;
pthread_cond_t threshold_cv;

void* edit_race(void *t) 
{
	long i;
	long my_id = (long)t;

	for (i=0; i<100,race<RACE_LIMIT; i++) 
	{
		pthread_mutex_lock(&mutex);
		if(my_id==2)
		{
		    race+=3;
		}
		else if(my_id==3)
		{
		    race-=1;
		}
		if (race >= RACE_LIMIT) 
		{
			pthread_cond_signal(&threshold_cv);
			printf("thread %ld, race = %ld  Threshold reached.\n", my_id, race);
		}
		printf("thread %ld, race = %ld\n", my_id, race);
		
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
	pthread_exit(NULL);
}

void *watch_race(void *t) 
{
	long my_id = (long)t;
	printf("Starting watch_race(): thread %ld\n", my_id);
	long t2=2, t3=3;
	pthread_t thread1, thread2;
	pthread_create(&thread1, NULL, edit_race, (void *)t2);
	pthread_create(&thread2, NULL, edit_race, (void *)t3);
	pthread_mutex_lock(&mutex);
	while (race<RACE_LIMIT) 
	{
		pthread_cond_wait(&threshold_cv, &mutex);
		printf("Thread %ld Condition signal received.\n", my_id);
	}
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}

long main ()
{
	long i,t1=1;
	pthread_t watch_thread;
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init (&threshold_cv, NULL);
	pthread_create(&watch_thread, NULL, watch_race, (void *)t1);
	pthread_join(watch_thread, NULL);
	printf ("Waited on watch_thread. Done.\n");
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&threshold_cv);
	pthread_exit(NULL);
}
