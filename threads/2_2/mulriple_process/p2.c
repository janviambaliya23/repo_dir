#include "header.h"

void main()
{
	char *p;
	int id;

	id=shmget(3,30*sizeof(char),IPC_CREAT|0664);
	if(id<0)
	{
		perror("shmget");
		return;
	}

	p=shmat(id,0,0);
	if(p<0)
	{
		perror("shmat");
		return;
	}

	printf("enter the value in memory 2:-");
	scanf("%s",p);

	shmdt(p);

}
