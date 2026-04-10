#include "header.h" 

void client_info();
void convert_data(char *);

static int counter=0,flag=0;
int server_sock,client_sock,len;
struct sockaddr_in server_id, client_id;
pthread_mutex_t lock;

void handler()
{
//	printf("handler call..\n");
	flag=1;
	close(server_sock);
}

void *thread(void *arg)
{
	pthread_mutex_lock(&lock);
	counter++;
	pthread_mutex_unlock(&lock);
	printf("client -> %d\n",counter);
	
	char s[30];
	int client=*(int *)arg;
	client_info();
	free(arg);

	while(1)
	{

		memset(s,0,sizeof(s));
		int n=read(client,s,sizeof(s));
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
		s[n]='\0';
		if((strcmp("byy",s)==0))
		{
			pthread_mutex_lock(&lock);
			counter = counter - 1;
			pthread_mutex_unlock(&lock);
			printf("client -> %d\n",counter);
			
			if((counter==0) == 1) {
				kill(getpid(),SIGTERM);
			}
		}
		convert_data(s);
		write(client,s,strlen(s)+1);
	}
	close(client);
	return NULL;
}
//////////////////////////////////////////////////////////////
int main(int argc,char **argv)
{
	if(argc!=3)
        {
                printf("USAGE:- ./server port_num IP_addr..\n");
                return 0;
        }

	server_sock=socket(AF_INET,SOCK_STREAM,0);
	if(server_sock<0)
	{
		perror("socket");
		return 0;
	}
	perror("socket");
	/////////////////////////////////////////////////////////////////////

	server_id.sin_family=AF_INET;
	server_id.sin_port=htons(atoi(argv[1]));
	server_id.sin_addr.s_addr=inet_addr(argv[2]);
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

	signal(SIGTERM,handler);
	pthread_mutex_init(&lock,NULL);
	while(flag==0)
	{
		client_sock=accept(server_sock,(struct sockaddr*)&client_id,&len);
		if(client_sock<0)
		{
		//if(flag==1)
		//		return 0;
			perror("accept");
			return 0;
		}
		perror("accept");
		
		int *pclient = malloc(sizeof(int));
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

