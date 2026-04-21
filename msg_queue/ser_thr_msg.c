#include "header.h"

struct sockaddr_in server_id, client_id;
void client_info();
void convert_data(char *);

void *thread(void *arg)
{
	char s[30];
	int client=*(int *)arg;
	client_info();
	free(arg);

	while(1)
	{
		//read(client,s,sizeof(s));
		read(client,s,sizeof(s));
			convert_data(s);
			if(strcmp("byy",s)==0)
				break;
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
/////////////////////////////////////////////////////////////////

	int server_sock,client_sock,len;
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

	while(1)
	{
		client_sock=accept(server_sock,(struct sockaddr*)&client_id,&len);
		if(client_sock<0)
		{
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
	close(server_sock);
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

