/* different semaphore condition.
Note:- semop decide which process should enter into critical section or not.*/

#include "header.h"
void main()
{
	int id,r;
	struct sembuf v;

	id=semget(4,5,IPC_CREAT|0664);
	if(id<0)
	{
		perror("semget");
		return;
	}
	printf("id=%d\n",id);
	///////////////////////////////////////////////////
	
	v.sem_num=2;
	v.sem_op=0 ;
	v.sem_flg=0;

	printf("before..\n");
	semop(id,&v,1);
	printf("after..\n");
}

