// p3 solution using mutex. 

#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

int mails=0;
pthread_mutex_t lock;

void *thread(void *arg)
{
	for(int i=0;i<1000000;i++)
	{
		pthread_mutex_lock(&lock);
		mails++;
		pthread_mutex_unlock(&lock);
	}
}
int main()
{
	pthread_t t1, t2;

	pthread_mutex_init(&lock,NULL);

	pthread_create(&t1,0,&thread,NULL);
	pthread_create(&t2,0,&thread,NULL);

	pthread_join(t1,0);
	pthread_join(t2,0);

	pthread_mutex_destroy(&lock);
	printf("number of mails-> %d\n",mails);
	return 0;
}
