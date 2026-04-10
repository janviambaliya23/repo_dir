/* QUESTION:- share memory + semaphore + 2 structure  and array of structure.
*/

#include "header.h"
#define n 2
void main()
{
	struct student *st;
	//int shm_id=shmget(3,sizeof(struct data),IPC_CREAT | 0664);
	int shm_id=shmget(3,n*sizeof(struct student),IPC_CREAT | 0664);
	if(shm_id<0)
	{
		perror("shmget");
		return;
	}

	st=(struct student*)shmat(shm_id,NULL,0);
	if(st<0)
	{
		perror("shmat");
		return;
	}
//////////////////////////////////////////////-- semaphore

	int sem_id=semget(4,1,IPC_CREAT|0664);
	if(sem_id>=0)
	{
		semctl(sem_id, 0, SETVAL, 1);
	}
	else
	{
	
		sem_id=semget(4,1,0664);
	}

	struct sembuf v;
	v.sem_flg=0;
	v.sem_num=0;
	
//-----------------------------------------
	printf("sizeof(student) = %lu\n", sizeof(struct student));
	v.sem_op=-1;
	semop(sem_id,&v,1);
	for(int i=0;i<n;i++)
	{
		printf("Enter rollno..\n");
		scanf("%d",&st[i].rollno);
		for(int j=0;j<n;j++)
		{
			printf("Enter the key..\n");
			scanf(" %d",&st[i].t[j].key);
			printf("Enter the msg..\n");
			scanf(" %s",st[i].t[j].msg);
		}
	}
	v.sem_op=1;
	semop(sem_id,&v,1);
	shmdt(st);
}
