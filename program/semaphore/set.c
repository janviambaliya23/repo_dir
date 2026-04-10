//how to set the value

#include "header.h"

void main(int argc, char **argv)
{
	int r,id;
	if(argc!=3)
	{
		printf("USAGE:- ./get, sem_number,  semaphore_value\n");
		return;
	}
	
	id=semget(4,5,IPC_CREAT|0664);	//  here, we are creating array of 5 int.
	if(id<0)
	{
		perror("semget");
		return;
	}
	printf("id-> %d\n",id);
///////////////////////////////////////////////////////////////////////////////////////////
// how to read

// ./get semnum
	r=semctl(id,atoi(argv[1]),SETVAL,atoi(argv[2]));
	if(r<0)
	{
		perror("semctl");
		return;
	}
	printf("r=%d\n",r);


//semctl(id, 0, IPC_RMID);
	
}

// I want to open semaphore set whose key is 1. if it is not there means create it.


