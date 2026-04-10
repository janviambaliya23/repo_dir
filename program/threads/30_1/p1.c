#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void *thread(void *arg)
{
	printf("Thread running\n");
	return NULL;
}

int main()
{
	pthread_t t1;
	pthread_attr_t attr;
	size_t stacksize;

	pthread_attr_init(&attr);


	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);	//Detached thread = self-cleaning:
	pthread_attr_setstacksize(&attr, 2*1024*1024);
	pthread_create(&t1,&attr,thread,NULL);
	pthread_attr_getstacksize(&attr,&stacksize);	// read back the stack size from attr object.
	printf("stack size-%zu\n",stacksize);

	pthread_attr_destroy(&attr);

}
