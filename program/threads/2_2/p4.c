// in parent:- write A to Z in shared memory
// in child:- access that memory and read whatever is written by parent.

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

	int r=fork();
	if(r==0)
	{
		printf("%s\n",p);
		shmdt(p);
	}
	else
	{
		int ch='A',i;
		for(int i=0;i<26;i++)
		{
			p[i]=ch++;
		}
		p[26]='\0';
		wait(0);	

		shmdt(p);

		shmctl(id, IPC_RMID, NULL);
	}

}
