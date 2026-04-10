//Design and implement a bidirectional communication system between two independent processes using a named pipe (FIFO) in C on a Linux system.
#include "header.h"

int main()
{
	mkfifo("myfifo1",0664);
	mkfifo("myfifo2",0664);

	int r=fork();
	if(r==0)
	{
		int fd1=open("myfifo2",O_RDONLY);
		if(fd1<=-1)
		{
			perror("open");
			return 0;
		}
		while(1)
		{
			char s[30];	
			read(fd1,s,sizeof(s));
			printf("msg is--> %s\n",s);

		}
	}
	else
	{	
		int fd=open("myfifo1",O_WRONLY);
		if(fd<=-1)
		{
			perror("open");
			return 0;
		}
		while(1)
		{
			char s[30];
			printf("Enter the msg-->");
			scanf(" %[^\n]",s);
			write(fd,s,strlen(s)+1);
			printf("\nmsg send..\n\n");
		}
	}
}
