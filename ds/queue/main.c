#include "header.h"

#define size 10

void main()
{
	int op;
	struct queue q;
	q.front = q.rear = -1;
	while(1)
	{
		printf("Enter the option...\n1)enqueue 2)dequeue 3)print 4)exit\n");
		scanf("%d",&op);
		switch(op)
		{
			case 1:enqueue(&q); break;
			case 2:int n=dequeue(&q);
			      printf("dequeue ary is-> %d\n",n); break;
			case 3:print(&q); break;
			case 4:exit(0); break;
			defualt:printf("UNKNOWN option..\n"); break;
		}
	}
}

void enqueue(struct queue *q)
{

	if(q->rear==size-1)
	{
		printf("queue is FULL..\n");
		return;
	}
	if(q->front==-1)
		q->front=0;

	int temp;
	printf("Enter the value..\n");
	scanf("%d",&temp);

	q->ary[++q->rear]=temp;   //-> ++rear -> ++(q->rear) -> add index 1st then increment rear value
	printf("%d inserted\n", temp);
}

int dequeue(struct queue *q)
{
	if(q->front==-1)
	{
		printf("queue is empty..\n");
		return -1;
	}
	int temp=q->ary[q->front];
	if(q->front == q->rear)
		q->front = q->rear = -1;
	else
		q->front++;
	return temp;
}

void print(struct queue *q)
{
	if(q->front==-1)
	{
		printf("queue is empty..\n");
		return;
	}

	for(int i=q->front; i<=q->rear;i++)
	{
		printf("%d ",q->ary[i]);
	}
	printf("\n");
}
