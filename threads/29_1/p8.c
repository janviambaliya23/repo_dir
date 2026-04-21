// write code for 2 way communication using thread.

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


void *thread(void *arg)
{
	char s[20];
	int fd=open("f1",O_WRONLY);
	while(1)
	{
		printf("Enter the string->\n");
		scanf("%s",s);
		write(fd,s,strlen(s)+1);
	}
}

void *thread1(void *arg)
{
	char s[20];
	int fd1=open("f2",O_RDONLY);
	while(1)
	{
		read(fd1,s,sizeof(s));
		printf("string is->%s\n",s);
	}
}

int main()
{
	pthread_t t1,t2;

	mkfifo("f1",0664);
	mkfifo("f2",0664);

	pthread_create(&t1,0,&thread,NULL);
	pthread_create(&t2,0,&thread1,NULL);


	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
//pthread_exit(0);
	return 0;
}
