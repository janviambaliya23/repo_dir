// msg queue server- client (server)

#include "header.h" 

void client_info();
void convert_data(char *);

int fd;
static int counter=0,flag=0;
int server_sock,client_sock,len,msgid;
struct sockaddr_in server_id, client_id;
pthread_mutex_t lock;

struct msgbuf v;

void handler()
{
	flag=1;
	close(server_sock);
}

void print_handler()
{
	printf("handler call...\n");
	FILE *fp =fopen("data","r");
	if(fp<0)
		perror("fopen");

	char ary[40];
	while(fgets(ary,40,fp))
	{
		printf("%s",ary);
	}
	printf("\n");
}

void *thread(void *arg)
{
	int client=*(int *)arg;
	client_info();
	free(arg);
	
	int id=0;
	read(client,&id,sizeof(id));
	printf("id is->%d\n",id);

	pthread_mutex_lock(&lock);
	counter++;
	v.client_id=id;
	printf("active client -> %d\n",counter);
	pthread_mutex_unlock(&lock);
	printf("client id before while--> %d\n\n",v.client_id);

	fd=open("data",O_RDWR | O_APPEND|O_CREAT,0664 );
	
	while(1)
	{

//		memset(&v,0,sizeof(v));
		int n=msgrcv(msgid,&v,sizeof(v) - sizeof(long),1,0);
		if(n==0)
		{
			printf("client close connection..\n");
			break;
		}
	
		if(n<0)
		{
			perror("read");
			break;
		}
		v.data[n]='\0';


	
		char buff[100];
		int data1=snprintf(buff,sizeof(buff),"client %d, data is->%s\n ",v.client_id,v.data);
		printf("client id-> %d\n",v.client_id);
		write(fd,buff,data1);


		if((strcmp("byy",v.data)==0))
		{
			pthread_mutex_lock(&lock);
			counter = counter - 1;
			pthread_mutex_unlock(&lock);
			printf("client disconnect -> %d\n",counter);
			
			if((counter==0) == 1) {
				kill(getpid(),SIGTERM);
			}
		}
			
		convert_data(v.data);
		printf("data send by client-> %s\n\n",v.data);
	}
	close(fd);
	close(client);
	return NULL;
}
//////////////////////////////////////////////////////////////
int main()
{

	server_sock=socket(AF_INET,SOCK_STREAM,0);
	if(server_sock<0)
	{
		perror("socket");
		return 0;
	}
	perror("socket");
/////////////////////////////////////////////////////////////////////

	server_id.sin_family=AF_INET;
	server_id.sin_port=htons(2000);
	server_id.sin_addr.s_addr=inet_addr("0.0.0.0");
	len=sizeof(server_id);
	if(bind(server_sock,(struct sockaddr *)&server_id,len)<0)
	{
		perror("bind");
		return 0;
	}
	perror("bind");
//////////////////////////////////////////////////////////////////////

	if(listen(server_sock,5)<0)
	{
		perror("listen");
		return 0;
	}
	perror("listen");
/////////////////////////////////////////////////////////////////////
	key_t key = ftok("logger_key", 65);
	msgid = msgget(key, IPC_CREAT | 0664);
	
	signal(SIGTERM,handler);
	signal(SIGUSR1,print_handler);
	pthread_mutex_init(&lock,NULL);
	while(flag==0)
	{
		client_sock=accept(server_sock,(struct sockaddr*)&client_id,&len);
		if(client_sock<0)
		{
			perror("accept");
			return 0;
		}
		perror("accept");
		
		char *pclient = malloc(sizeof(char) *4);
		*pclient=client_sock;

		pthread_t th;
		pthread_create(&th,0,thread,pclient);

		pthread_detach(th);
	}
	pthread_mutex_destroy(&lock);
}

void client_info()
{
	printf("client port no:- %d\n",ntohs(client_id.sin_port));
	printf("client ip_address:%s\n",inet_ntoa(client_id.sin_addr));

}

void convert_data(char *s)
{
	for(int i=0;s[i];i++)
	{
		if(s[i]>='A' && s[i]<='Z')
		{
			s[i]=s[i]+32;
		}
		else if(s[i]>='a' && s[i]<='z')
		{
			s[i]=s[i]-32;
		}
	}
}

