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
//	dup2(fd,STDOUT_FILENO);
//	fflush(stdout);
	int id=semget(4,5,IPC_CREAT|0664);
	if(id<0)
	{
		perror("semget");
		return;
	}

	struct sembuf v;

	v.sem_num=3;
	v.sem_op=0;
	v.sem_flg=0;
	ch=1;
	for(int i=0;i<10;i++)
	{
		semop(id,&v,1);
		semctl(id,2,SETVAL,1);
		char buf[20];
                int n=snprintf(buf,sizeof(buf),"%d ",ch);
                write(fd,buf,strlen(buf));

//		fprintf(stderr,"%c ",ch);
//		printf("%c ",ch);
		ch+=2;
		semctl(id,3,SETVAL,1);
		semctl(id,2,SETVAL,0);
	}
}
