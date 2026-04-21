#include"header.h"

char st1[20],st2[20];
char result[40];

pthread_cond_t cond1;
pthread_cond_t cond2;
pthread_mutex_t lock;

static int flag1=0,flag2=0;

void *input1(void *arg)
{
	pthread_mutex_lock(&lock);
	printf("Enter the value...\n");
	scanf(" %[^\n]",st1);
	printf("string 1--> %s\n",st1);
	
	flag1=1;
	pthread_cond_signal(&cond1);
	pthread_mutex_unlock(&lock);

	return NULL;
}

void *input2(void *arg)
{
	pthread_mutex_lock(&lock);
	while(flag1==0)
	{
		pthread_cond_wait(&cond1,&lock);
	}
	printf("Enter the value...\n");
	scanf(" %[^\n]",st2);
	printf("string 2--> %s\n",st2);
	flag2=1;
	pthread_cond_signal(&cond2);
	pthread_mutex_unlock(&lock);

	return NULL;	
}
void *result_thread(void *arg)
{
	pthread_mutex_lock(&lock);
        while(flag2==0)
        {
                pthread_cond_wait(&cond2,&lock);
        }
	printf("frpm thread number 3...\n\n");
	printf("string 1--> %s\n",st1);
        printf("string 2--> %s\n",st2);
        pthread_mutex_unlock(&lock);

	return NULL;
}

int main()
{
	pthread_t th[3];

	pthread_mutex_init(&lock,NULL);
	pthread_cond_init(&cond1,NULL);
	pthread_cond_init(&cond2,NULL);

	pthread_create(&th[0],NULL,&input1,0);
	pthread_create(&th[1],NULL,&input2,0);
	pthread_create(&th[2],NULL,&result_thread,0);

	pthread_join(th[0],NULL);
	pthread_join(th[1],NULL);
	pthread_join(th[2],NULL);

	pthread_cond_destroy(&cond1);
	pthread_cond_destroy(&cond2);

	pthread_mutex_destroy(&lock);

}
