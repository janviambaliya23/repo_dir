// increment variable from both threads.
#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>


int x=2;
void *thread(void *arg)
{
	x++;
	sleep(3);
	printf("Value of x in t1->%d\n",x);
}

void *thread1(void *arg)
{
	sleep(3);
	printf("Value of x in t1->%d\n",x);
}
int main()
{
	pthread_t t1, t2;
	pthread_create(&t1,0,&thread,NULL);
	pthread_create(&t2,0,&thread1,NULL);

	pthread_join(t1,0);
	pthread_join(t2,0);
	return 0;
}
