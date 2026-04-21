//reader

#include "header.h"

int main()
{
	int fd=shm_open("/mymap",O_CREAT|O_RDWR,0664);
	if(fd<0)
	{
		perror("shm_open");
		return 0;
	}

	//ftruncate(fd,sizeof(struct shmdata));

	struct shmdata *mapping=mmap(0,sizeof(struct shmdata),PROT_WRITE|PROT_READ,MAP_SHARED,fd,0);
	if(mapping==MAP_FAILED)
	{
		perror("mmap");
		return 0;
	}
		
	sem_t *sem=sem_open("/mysem",0);
        sem_t *mutex=sem_open("/mymutex",0);
        if(sem==SEM_FAILED || mutex==SEM_FAILED)
        {
                perror("sem_open");
                return 0;
        }

	int c=-1;

	printf("waiting..\n");
	while(1)
	{
		sem_wait(sem);
		sem_wait(mutex);
		if(mapping->count!=c)
		{
			c=mapping->count;

			for(int i=0;i<5;i++)
				printf("%d ",mapping->ary[i]);

			printf("\n");
		}
		sem_post(mutex);
		sem_post(sem);
	}

	close(fd);
}
