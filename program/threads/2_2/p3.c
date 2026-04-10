#include "header.h"

int main()
{

	char *p;
	int id=shmget(5,50,IPC_CREAT|0664);
	if(id<0)
	{
		perror("shmget");
		return 0;
	}	

	p=shmat(id,0,0);
	if(p<0)
	{
		perror("shmat");
		return 0;
	}

	printf("Enter the data..\n");
	scanf("%s",p);

	shmdt(p);

}
