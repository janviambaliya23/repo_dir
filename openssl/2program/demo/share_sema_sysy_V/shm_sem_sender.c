/*Question:----
 use shared memory using system v call and semaphore.
 sender print msg then receiver print but after 1 sec. and then after again sender 1 print but this time after 2 sec. 
 sender print -> after 2 sec delay
 receiver print -> after 1 sec delay
----------------------------------------------------------------------
NOTE:-  here we are not using get and op and set program that is why we need to use semctl function.

Semaphore = 1 chair 🪑
SETVAL(1) → chair exists
sem_op = -1 → someone sits → chair becomes unavailable

Without SETVAL:
No chair exists → everyone waits forever 😄

you should NOT call semctl(...SETVAL...) in both processes.
----------------
🔴 VERY IMPORTANT RULE
malloc() memory is NEVER shared between processes
👉 Each process has its own virtual memory
-----------------
*/


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
	semctl(sem_id, 0, SETVAL, 1);
	
	struct sembuf v;
	v.sem_num=0;
	v.sem_flg=0;

	while(1)
	{
		v.sem_op=-1;	// lock	1 -> 0
		semop(sem_id,&v,1);
		printf("msg from process 1..\n");
		sleep(1);
		v.sem_op=1;	// unlock  0 -> 1
		semop(sem_id,&v,1);
	}
	shmdt(shm_at);
}
