// circular queue.

#include "header.h"

#define size 4

static int first=-1,second=-1;
static int TOP=-1;
char que[size][1024];

void enqueue()
{
	printf("system clear...\n");
	if((second+1)%size==first)
	{
		printf("queue is overflow\n");
		return;
	}
	if(first==-1)
		first=0;
	second=(second+1)%size;

	printf("enter enqueue num");
	scanf(" %[^\n]",que[second]);	// read full line
}
void dequeue()
{
	if(first==-1)
	{
		printf("queue is empty..\n");
		return;
	}
	printf("deleted->  %s\n",que[first]);
	if(first==second)
		first=second=-1;
	else
		first=(first+1)%size;
}

void display()
{
	if(first<=-1)
	{
		printf("queue is empty\n");
		return;
	}
	int i=first;
	printf("queue elements....\n");

	for( ;i<=second; )
	{
		printf("%s\n",que[i]);
		i=(i+1)%size;
	}
}

int main()
{
	int op;
	while(1)
	{
		printf("enter choice\n");
		printf("1)enqueue 2)dequeue 3)display 4)exit\n");
		scanf("%d",&op);
		switch(op){
			case 1: enqueue();break;
			case 2: dequeue();break;
			case 3: display();break;
			case 4: exit(0);
			default:printf("unknown choice");
		} 
	}

}
