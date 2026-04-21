// ds + thread
// 1 thread add data in single link list
// 2 thread delete data from SLL.

#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>

#define max 5

typedef struct job
{
	int ary;
	struct job *next;
}SLL;

pthread_mutex_t lock;
pthread_cond_t cond;
SLL *headptr=0;
int count=0;

void add(SLL **ptr)
{
		SLL *new=malloc(sizeof(SLL));
		printf("Enter the job..\n");
		scanf("%d",&new->ary);

		if(*ptr==0)
		{
			*ptr=new;
		}
		else
		{
			SLL *last=*ptr;
			while(last->next)
				last=last->next;

			last->next=new;
		}
}
void rem(SLL **ptr)
{
		SLL *del=*ptr,*last;
		if(*ptr!=0)
		{
			last=del->next;
			*ptr=last;
			free(del);
			del=last;
			return;
		}
		else
		{
			printf("no record found..\n");
			return;
		}
}

void print(SLL *ptr)
{
	if(ptr==0)
	{
		printf("No record found..\n");
		return;
	}
	while(ptr)
	{
		printf("%d  ",ptr->ary);
		ptr=ptr->next;
	}
	printf("\n");

}

void *add_thread(void *arg)
{
	while(1)
	{
		pthread_mutex_lock(&lock);
		while(count>max)
			pthread_cond_wait(&cond,&lock);

			add(&headptr);
			count++;
			print(headptr);
	
		
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}

void *remove_thread(void *arg)
{
	while(1)
	{
		pthread_mutex_lock(&lock);

		while(count<max)
			pthread_cond_wait(&cond,&lock);
		if(count>max)
		{
			rem(&headptr);
			count--;
			print(headptr);
		}
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}

int main()
{
	pthread_t th[2];

	pthread_mutex_init(&lock,NULL);
	pthread_cond_init(&cond,NULL);

	pthread_create(&th[0],NULL,&add_thread,NULL);
	pthread_create(&th[1],NULL,&remove_thread,NULL);

	pthread_join(th[0],NULL);
	pthread_join(th[1],NULL);

	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&cond);
}


