// how to get our thread return value in main function.

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>


void *thread(void *arg)
{
	int value=(rand() %6) +1;

	//printf("value=%d\n",value);
	//return &value;   invalid so allocate malloc memory
	int *res=malloc(sizeof(int));
	*res=value;
//	pthread_exit(res);
	return (void *)res;
}

int main()
{

	int *result;

	pthread_t th;
	pthread_create(&th,0,thread,NULL);


	pthread_join(th,(void **)&result);

	printf("value=%d\n",*result);
	free(result);
	return 0;
}
