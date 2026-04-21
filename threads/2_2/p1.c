/* The Scenario: You have two threads: a Reader and a Processor.
   The Reader reads a number randomly.
   The Processor squares that number ($n^2$) and prints the result.*/

#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

pthread_mutex_t lock;
pthread_cond_t cond;
int num,flag=0;

void *thread1(void *arg)
{
	while(1)
	{	
		pthread_mutex_lock(&lock);
		while(flag==1)
			pthread_cond_wait(&cond,&lock);

		num=(rand()%11)+1;
		printf("\n\nnumber change in th1\n");
		flag=1;
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}

void *thread2( void *arg)
{
	while(1)
	{
	pthread_mutex_lock(&lock);
	while(flag==0)
		pthread_cond_wait(&cond,&lock);

	printf("multiple of %d is %d\n",num,(num*num));
	flag=0;
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&lock);
	//sleep(1);
	}
	return NULL;
}

int main()
{
	pthread_t th1,th2;

	srand(getpid());
	pthread_mutex_init(&lock,NULL);
	pthread_cond_init(&cond, NULL);

	pthread_create(&th1,NULL,&thread1,NULL);
	pthread_create(&th2,NULL,&thread2,NULL);

	pthread_join(th1,NULL);
	pthread_join(th2,NULL);
	

	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&cond);

	return 0;
}
