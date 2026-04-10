// add array of 5 integer from server and client print that integer.


#include "header.h"

void main()
{

	int *p,id;

	id=shmget(3,5*sizeof(int),IPC_CREAT|0664);
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

	printf("Enter the array element..\n");
	for(int i=0;i<5 ;i++)
	{
		scanf("%d",&p[i]);
	}

	shmdt(p);

}
