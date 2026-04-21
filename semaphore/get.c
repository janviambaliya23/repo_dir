//how to create and open semaphore set and how to read(get) the value

#include "header.h"

// how to create
void main(int argc, char **argv)
{
	if(argc!=2)
	{
		printf("USAGE:- ./get semaphore_value\n");
		return;
	}
	
	int id=semget(4,5,IPC_CREAT|0664);	//  here, we are creating array of 5 int.
	if(id<0)
	{
		perror("semget");
		return;
	}
	printf("id-> %d\n",id);
///////////////////////////////////////////////////////////////////////////////////////////
// how to read

// ./get semnum
	int r=semctl(id,atoi(argv[1]),GETVAL);
	if(r<0)
	{
		perror("semctl");
		return;
	}
	printf("r=%d\n",r);


	
}

// I want to open semaphore set whose key is 1. if it is not there means create it.


