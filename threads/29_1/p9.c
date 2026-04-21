// create 5 threads, each taking a unique prime from the primes array and print it on screen.

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int prime[5]={2,3,7,11,13};

void *thread(void *arg)
{
	int index=*(int *)arg;
	printf("%d ",prime[index]);
	free(arg);
}

int main()
{
	pthread_t th[5];
//	int i;
	for(int i=0;i<5;i++)
	{
		int *a=malloc(sizeof(int));
		*a=i;
		pthread_create(th+i,0,&thread,a);
	}

	for(int i=0;i<5;i++)
	{
		pthread_join(th[i],NULL);
	}
}

// between thread creat to started the value inside that thread is changing that is why you get 0 and duplicate value as result.
// to avoid this problem allocate new memory block for each thread creation which will avoid problem of dumplication.
// if you want to only remove 0 from output and want duplicate then just simply use "int i" outof the for loop.if you will write inside the for loop then you will get 0 in your output.
