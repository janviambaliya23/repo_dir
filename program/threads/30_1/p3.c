/*
Write a program where:
One thread waits until a value becomes greater than 10
Another thread increments the value*/

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>

int count=0,flag=0;

pthread_mutex_t lock;
pthread_cond_t cond;

void *thread(void *arg)
{
	while(1)
	{
		pthread_mutex_lock(&lock);

		count++;
		if(count>10)
		{	
			pthread_cond_signal(&cond);
		}
		if(count == 12)
			break;
		pthread_mutex_unlock(&lock);
		sleep(1);
	}

}

void *thread2(void *arg)
{

		pthread_mutex_lock(&lock);
		
		while(count<=10)
		{
			printf("thread 2 is waiting...\n");
			pthread_cond_wait(&cond,&lock);
		}
		
		printf("from t2 = %d\n",count);
		pthread_mutex_unlock(&lock);

}

int main()
{
	pthread_t t1,t2;

	pthread_mutex_init(&lock,NULL);
	pthread_cond_init(&cond,NULL);

	pthread_create(&t1,NULL,&thread,NULL);
	pthread_create(&t2,NULL,&thread2,NULL);

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);

	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&cond);

}
