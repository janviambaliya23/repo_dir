#include "header.h"

void main()
{
//////////////////////////////////////////////////////////-- shared memory
	int shm_id=shmget(1,1,IPC_CREAT|0664);
	if(shm_id<0)
	{
		perror("shmget");
		return;
	}
	void *shm_at;
	shm_at=shmat(shm_id,0,0);
	if(shm_at<0)
	{
		perror("shmat");
		return;
	}

//////////////////////////////////////////////////////////-- semaphore
	int sem_id= semget(2,1,IPC_CREAT|0664);
	if(sem_id<0)
	{
		perror("semget");
		return;
	}
//semctl(sem_id, 0, SETVAL, 1);	
	struct sembuf v;
	v.sem_num=0;
	v.sem_flg=0;
//////////////////////////////////////////////////////////////-- structure
	while(1)
	{
	
		v.sem_op=-1;    // lock 1 -> 0
                semop(sem_id,&v,1);
                printf("from process 2....\n");
                sleep(2);
                v.sem_op=1;     // unlock  0 -> 1
                semop(sem_id,&v,1);
	}
	shmdt(shm_at);
	shmctl(shm_id, IPC_RMID, NULL);
}
