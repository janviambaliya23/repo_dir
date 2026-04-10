#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

void *thread(void *arg)
{
	printf("inside the thread\n");
	sleep(3);
	printf("Ending the threads..\n");
}

int main()
{
	pthread_t t1, t2;
	pthread_create(&t1,0,&thread,NULL);
	if(pthread_create(&t2,0,&thread,NULL)!=0){
	return 1;
	}

	pthread_join(t1,0);
	if(pthread_join(t2,0)!=0){
	return 2;
	}
	return 0;
}

// here both thread run concurrently. 
