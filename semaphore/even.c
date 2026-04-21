#include "header.h"

void main()
{
	char ch;

	int fd=open("file",O_WRONLY|O_APPEND|O_CREAT,0664);
	if(fd<0)
	{
		perror("open");
		return;
	}
	int id=semget(4,5,IPC_CREAT|0664);
	if(id<0)
	{
		perror("semget");
		return;
	}

	struct sembuf v;

	v.sem_num=2;
	v.sem_op=0;
	v.sem_flg=0;
	ch=0;
	for(int i=0;i<10;i++)
	{
		semop(id,&v,1);
		semctl(id,3,SETVAL,1);

		char buf[20];
		int n=snprintf(buf,sizeof(buf),"%d ",ch);
		write(fd,buf,strlen(buf)); // if i write sizeof() then in file othr 19 byte will also print in the form of garbage.
		ch+=2;

		semctl(id,2,SETVAL,1);
		semctl(id,3,SETVAL,0);
	}
}
