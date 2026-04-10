// what is an race condition. here we can not get our desier output. this is race condition.
#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

int mails=0;
void *thread(void *arg)
{
	for(int i=0;i<1000000;i++)
	mails++;
}
/* steps to remove bugs-----------------------
-> read mails
-> increment
-> write mails

*/
int main()
{
	pthread_t t1, t2;
	pthread_create(&t1,0,&thread,NULL);
	pthread_create(&t2,0,&thread,NULL);

	pthread_join(t1,0);
	pthread_join(t2,0);

	printf("number of mails-> %d\n",mails);
	return 0;
}
