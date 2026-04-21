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

	v.sem_num=2;	// this process will check 2nd sema.
	v.sem_op=0;
	v.sem_flg=0;
	
	
	char ch;
	for(ch='a';ch<='z';ch++)
	{
		semop(id,&v,1);// blocking fun.  AS LONG AS 2nd sema is 0 it will allow this process to do furthere task.
		semctl(id,3,SETVAL,1); // setting 2nd semaphore as 1
		write(fd,&ch,1);
		semctl(id,2,SETVAL,1);
		//sleep(1);
		semctl(id,3,SETVAL,0);
	}

	printf("Done..\n");

}


// it will check(setisfy then only enter into process) 2nd sema. but set 3rd sema.
