#include "header.h"

int id,flag=0,flag1=0;

pthread_mutex_t lock;
pthread_cond_t cond;
T *p;

void *read_thread(void *arg)
{
	p=shmat(id,NULL,0);

	T *data;
	data=malloc(sizeof(T));
	strcpy(data->msg,"VVDN TECHNOLOGY...");
	printf("%s\n",data->msg);

	time_t Time;
	struct tm *tm_info;

	struct timespec ts;
	while(1)
	{
		pthread_mutex_lock(&lock);

		Time=time(NULL);
		tm_info=localtime(&Time);


		strftime(data->time,sizeof(data->time),"%H:%M:%S",tm_info);
		strftime(data->day,sizeof(data->day),"%d-%m-%y",tm_info);


	//	printf("time %s --> day  %s\n",data->time, data->day);

		clock_gettime(CLOCK_REALTIME,&ts);
		ts.tv_sec +=2;

		int rec=pthread_cond_timedwait(&cond,&lock,&ts);

		if(rec==ETIMEDOUT)
		{
			p=data;
			//printf("data done writing..\n");
			fprintf(stderr,"data done writing..\n");
			flag=1;
			flag1=1;
			pthread_cond_signal(&cond);
		}

		pthread_mutex_unlock(&lock);
	}
	shmdt(p);
	return NULL;
}

void *write_thread(void *arg)
{
	T *data=malloc(sizeof(T));
	char file_name[20]="LOG.txt";
//	FILE *fp=fopen(file_name,"a+");
	int fd=open(file_name,O_WRONLY|O_CREAT|O_APPEND,0664);
	struct stat st;
	int count=1;
	dup2(fd,1);
	
	while(1)
	{
		pthread_mutex_lock(&lock);

		stat(file_name,&st);

		if(st.st_size>=500)
		{
			count++;
		//	fclose(fp);
			close(fd);

			snprintf(file_name,sizeof(file_name),"LOG%d.txt",count);

			//fp=fopen(file_name,"a+");
			 fd=open(file_name,O_WRONLY|O_CREAT|O_APPEND,0664);
			dup2(fd,1);	
		}

		while(flag==0)
			pthread_cond_wait(&cond,&lock);
		flag=0;
		if(flag1)
		{
			*data=*p;
			printf("TIME: %s %s, msg->%s \n",data->time, data->day, data->msg);
			//fprintf(fp,"TIME: %s %s, msg->%s \n",data->time, data->day, data->msg);
			
			fflush(stdout);
			//write(fd,&data,sizeof(data)); it will print garbage value. 
			
			
			flag1=0;
		}
		
		pthread_mutex_unlock(&lock);
	
	}

	return NULL;
}

int main()
{
	id=shmget(1,sizeof(T),IPC_CREAT|0664);


	pthread_t t1,t2;

	pthread_mutex_init(&lock,NULL);
	pthread_cond_init(&cond,NULL);

	pthread_create(&t1,NULL,&read_thread,NULL);
	pthread_create(&t2,NULL,&write_thread,NULL);

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);

	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&cond);

	shmctl(id, IPC_RMID, NULL);
}
