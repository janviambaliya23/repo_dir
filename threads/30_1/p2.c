// simple example of incrementing gloable data with mutex and conditional variable.
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
		while(flag==0)
		{
			pthread_cond_wait(&cond,&lock);
		}
		count++;
		flag^=1;;
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&lock);
		printf("count t1 -> %d\n",count);
		sleep(1);

		if(count>=20)
		{
			pthread_mutex_unlock(&lock);
			break;
		}
	}
}

void *thread2(void *arg)
{
	while(1)
	{
		pthread_mutex_lock(&lock);
		while(flag==1)
		{
			pthread_cond_wait(&cond,&lock);
		}
		count++;
		flag^=1;
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&lock);
		printf("count t2 -> %d\n",count);
		sleep(1);
		if(count>=20)
		{
			pthread_mutex_unlock(&lock);
			break;
		}
	}
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

	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&lock);
}
