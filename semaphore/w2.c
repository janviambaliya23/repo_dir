//HINT:- use wait for 0 condition.

#include "header.h"

void main()
{
	int id=semget(4,5,IPC_CREAT|0664);
	if(id<0)
	{
		perror("semget");
		return;
	}

	int fd=open("data",O_APPEND|O_WRONLY|O_CREAT,0664);	
	if(fd<0)
	{
		perror("open");
		return;
	}

	struct sembuf v;

	v.sem_num=2;
	v.sem_op=0;
	v.sem_flg=0;
	printf("before..\n");
	semop(id,&v,1);
	semctl(id,2,SETVAL,1); // setting 2nd semaphore as 1
	printf("after..\n");

	char ch;
	for(ch='A';ch<='Z';ch++)
	{
		write(fd,&ch,1);
		sleep(1);
	}

	semctl(id,2,SETVAL,0);
	printf("Done..\n");
}
