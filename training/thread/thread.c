#include "header.h"

int ary[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
static int count;
int idx;
pthread_mutex_t lock;

void *child_thread(void *n)
{
	int sum,i;
	int *p=(int *)n;
	pthread_mutex_lock(&lock);
	for(i=0;i<4;i++)
	{
		sum+=ary[idx];
		idx++;
	}
	printf("sum from thread %d is ->%d\n",*p,sum);
	count+=sum;
	pthread_mutex_unlock(&lock);
	return NULL;
}


int main()
{
	pthread_t th;
	pthread_mutex_init(&lock,NULL);
	idx=0;
	for(int i=0;i<5;i++)
	{
		pthread_create(&th,0,child_thread,&i);
		pthread_join(th,NULL);
	}

	pthread_mutex_destroy(&lock);
	printf("total count of ary is--> %d\n",count);
}
