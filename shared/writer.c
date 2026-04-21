//writer
//NOTE:-  writer should create and destroy the sem memory adn reader should read and print it only.

#include "header.h"

void handler(int );
int fd,pid,*temp;
sem_t *sem,*mutex;

int main()
{
	pid=getpid();
	printf("wait pid--> %d\n ",pid);
	fd=shm_open("/mymap",O_RDWR|O_CREAT,0664);
	if(fd<0)
	{
		perror("shm_open");
		return 0;
	}

	ftruncate(fd,sizeof(struct shmdata));

	struct shmdata *mapping=mmap(0,sizeof(struct shmdata),PROT_WRITE|PROT_READ,MAP_SHARED,fd,0);
	if(mapping==MAP_FAILED)
	{
		perror("mmap");
		return 0;
	}
	
	sem=sem_open("/mysem",O_CREAT,0664,0);
	mutex=sem_open("/mymutex",O_CREAT,0664,1);
	if(sem==SEM_FAILED || mutex==SEM_FAILED)
	{
		perror("sem_open");
		return 0;
	}

	sem_wait(mutex);
	mapping->count=0;
	sem_post(mutex);

	signal(SIGINT,handler);

	temp=malloc(sizeof(int)*5);
	while(1)
	{

		printf("Enter the 5 array elemen..\n");
		for(int i=0;i<5;i++)	
			scanf("%d",&temp[i]);

		sem_wait(mutex);
		for(int i=0;i<5;i++)
			mapping->ary[i]=temp[i];
		mapping->count++;
		sem_post(mutex);
		
		sem_post(sem);
	}
	munmap(mapping,sizeof(struct shmdata));
}


void handler(int argv)
{
	printf("\nclean up process done..\n");
	sem_unlink("/mymutex");	// semaphore obj delete
        sem_unlink("/mysem");
        shm_unlink("/mymap");	// shared memory obj delete
	close(fd);
	free(temp);
	if(argv==SIGINT)
	{
		printf("inside if condition..\n");
		kill(pid,SIGTERM);
		return;
	}
}
