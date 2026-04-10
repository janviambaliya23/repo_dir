/* QUESTION:- share memory + semaphore + structure  and array of structure.
----------------------------------------------------------------------🔴 VERY IMPORTANT RULE
malloc() memory is NEVER shared between processes
👉 Each process has its own virtual memory
-------------
malloc allocates process-local memory, so it cannot be shared. For IPC, data must be placed in shared memory using shmat().
------------
we must and need to add shmat in both process. if you want to delete memory as well then use semctl. this will help you to delete memory as well. 
	"shmctl(shm_id, IPC_RMID, NULL);"
shmdt only dettach from memory but memory is still there.


for make list use :-   ipcs
remove share memory:-  ipcrm -m <key>
remove semaphore :-    ipcrm -s <key>

*/

#include "header.h"
#define n 2

void main()
{
	struct data *st;
	//int shm_id=shmget(3,sizeof(struct data),IPC_CREAT | 0664);
	int shm_id=shmget(3,n*sizeof(struct data),IPC_CREAT | 0664);
	if(shm_id<0)
	{
		perror("shmget");
		return;
	}

	st=(struct data*)shmat(shm_id,NULL,0);
	if(st==NULL)
	{
		perror("shmat");
		return;
	}
//////////////////////////////////////////////-- semaphore

	int sem_id=semget(4,1,IPC_CREAT|0664);
	if(sem_id<0)
	{
		perror("semget");
		return;
	}

	struct sembuf v;
	v.sem_flg=0;
	v.sem_num=0;
	semctl(sem_id, 0, SETVAL, 1);
//-----------------------------------------

	v.sem_op=-1;
	semop(sem_id,&v,1);
	for(int i=0;i<n;i++)
	{
		printf("Enter the key..\n");
		scanf("%d",&st[i].key);
		printf("Enter the msg..\n");
		scanf("%s",st[i].msg);
	}
	v.sem_op=1;
	semop(sem_id,&v,1);

	shmdt(st);
}
