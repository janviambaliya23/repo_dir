#include "header.h"
#define n 2
void main()
{
	struct data *st;
	int shm_id=shmget(3,n*sizeof(struct data),IPC_CREAT|0664);
	if(shm_id<0)
	{
		perror("shmget");
		return;
	}

	st=shmat(shm_id,NULL,0);
	if(st<0)
	{
		perror("shmat");
		return;
	}
///////////////////////////////////////////////////-- semaphore

	int sem_id=semget(4,1,IPC_CREAT|0664);
	if(sem_id<0)
	{
		perror("semget");
		return;
	}
	struct sembuf v;
	v.sem_num=0;
	v.sem_flg=0;
	
/////////////////////////////////////////////////-- main logic

	v.sem_op=-1;
	semop(sem_id,&v,1);
	for(int i=0;i<n;i++)
	{
		printf("key is--> %d\n",st[i].key);
		printf("msg is --> %s\n",st[i].msg);
	}
	v.sem_op=1;
	semop(sem_id,&v,1);


	shmdt(st);
	shmctl(shm_id, IPC_RMID, NULL);
}
