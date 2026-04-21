// take thread number from user and return random number from thread into main function with multithread.

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

//int value;
void *thread(void *arg)
{
	int value=(rand()%10)+1;
	int *res=malloc(sizeof(int));
	*res=value;
	 return res;
}

int main()
{
	int n,i;
	printf("how many thread you wanr to creat...\n");
	scanf("%d",&n);

	int *p;
	srand(getpid());
	
	pthread_t th[n];
	for(i=0;i<n;i++)
	{
		pthread_create(&th[i],0,&thread,NULL);

		pthread_join(th[i],(void **)&p);
		printf("thread %d give value->%d\n",i,*p);
	}

	return 0;
}

/*

~ rand() uses ONE global random state per process
~ srand() resets that global state
~ When you call srand() inside each thread, you keep resetting the generator
~ When you call srand() once in main(), the state moves forward naturally
*/
