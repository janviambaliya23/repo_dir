#include "header.h"

#define size 4
static int TOP=-1;
char que[size][1024];

void enqueue()
{
	printf("system clear...\n");
	if(TOP>=size-1)
	{
		printf("queue is overflow\n");
		return;
	}
	TOP++;

	printf("enter enqueue num");
	scanf(" %[^\n]",que[TOP]);	// read full line
}
void dequeue()
{
	if(TOP<=-1)
	{
		printf("queue is empty..\n");
		return;
	}
	for(int i=0;i<TOP;i++)
		strcpy(que[i],que[i+1]);
	TOP--;

}

void display()
{
	if(TOP<=-1)
	{
		printf("queue is empty\n");
		return;
	}
	for(int i=0;i<=TOP;i++)
		printf("%s\n",que[i]);
	printf("\n");
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
