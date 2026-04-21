// array of threds. 

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
	int i;
	pthread_t th[4];
	pthread_mutex_init(&lock,NULL);
	
	for(int i=0;i<4;i++)
	{
		pthread_create(&th[i],0,&thread,NULL);

		printf("thread %d has started\n",i);
		pthread_join(th[i],0);
		printf("thread %d finish.\n",i);
	}
	pthread_mutex_destroy(&lock);
	printf("number of mails-> %d\n",mails);
	return 0;
}
// here, 4 thread create and after compliting 1 thread it finish and next thread is creating.
// while in other case if i write thread creation in one for loop and in other for loop if i write joint function of thread then in this case all 4 thread will concurretly run and then after it will finish . 
