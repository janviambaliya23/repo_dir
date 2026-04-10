#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

pthread_attr_t attr ,attr1;
size_t stacksize;

void *thread(void *arg)
{
	int a[99999999];
	printf("Thread running\n");
	pthread_attr_getstacksize(&attr,&stacksize);	// read back the stack size from attr object.
	printf("thread stack size-%zu\n",stacksize);
	return NULL;
}
/////////////////////////////////////////////////////////////////////////
void *t1(void *arg){
	printf("t1\n");
	pthread_getattr_np(pthread_self(), &attr);
	pthread_attr_getstacksize(&attr, &stacksize);
	printf("t1 stack size-%zu\n",stacksize);
	return NULL;
}
///////////////////////////////////////////////////////////////////////
int main()
{
	pthread_t t[2];

	pthread_attr_init(&attr);
	pthread_attr_init(&attr1);
	
	pthread_attr_setguardsize(&attr, 4096);
//	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);	//Detached thread = self-cleaning:
	pthread_attr_setstacksize(&attr, 1024*1024);
	pthread_create(&t[0],&attr,thread,NULL);
	
	printf("reached\n");

	pthread_create(&t[1],0,t1,NULL);
	perror("create");	

	//	pthread_exit(0);
	pthread_join(t[0] , NULL);
	pthread_join(t[1] , NULL);

	pthread_attr_destroy(&attr);

}	
