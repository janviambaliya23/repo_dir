#include "header.h"

int main(int argc, char **argv)
{
	if(argc!=3)
	{
		printf("USAGE:- ./server port_num IP_addr..\n");
		return 0;
	}


	int server_sock, client_sock,len;
	
	server_sock=socket(AF_INET,SOCK_STREAM,0);	
	if(server_sock<0)
	{
		perror("socket");
		return 0;
	}
	perror("socket");

	struct sockaddr_in server_id, client_id;
	server_id.sin_family=AF_INET;
	server_id.sin_port=htons(atoi(argv[1]));
	server_id.sin_addr.s_addr=atoi(argv[2]);
	len=sizeof(server_id);
	if(bind(server_sock,(struct sockaddr *)&server_id,len)<0)
	{
		perror("bind");
		return 0;
	}	
	perror("bind");

	if(listen(server_sock,5)<0)
	{
		perror("listen");
		return 0;
	}
	perror("listen");
		
	client_sock=accept(server_sock,(struct sockaddr*)&client_id,&len);
	if(client_sock<0)
	{
		perror("accept");
		return 0;
	}
	perror("accept");

		char s[30];
	while(1)
	{
		read(client_sock,&s,sizeof(s));
		printf("received data is--> %s\n",s);

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

		write(client_sock,&s,strlen(s));
		//	printf("new string is--> %s\n",s);
	}
	close(server_sock);
	close(client_sock);
}
