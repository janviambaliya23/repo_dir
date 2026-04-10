#include "header.h"

struct sockaddr_in server_id, client_id;

void client_info();
void convert_data(char *);

int main(int argc, char **argv)
{	
	int server_sock, client_sock,len;
	char s[30];

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
	server_id.sin_addr.s_addr=atoi(argv[2]);
	len=sizeof(server_id);
	if(bind(server_sock,(struct sockaddr*)&server_id,len)<0)
	{
		perror("bind");
		return 0;		
	}
	perror("bind");
//////////////////////////////////////////////////////////////////////
	int l;
	l=listen(server_sock,5);
	if(l<0)
	{
		perror("listen");
		return 0;
	}
	perror("listen");
////////////////////////////////////////////////////////////////////
	while(1)
	{
		printf("waiting for client request..\n");
		client_sock=accept(server_sock,(struct sockaddr *)&client_id,&len);
		if(client_sock<0)
		{
			perror("accept");
			return 0;
		}
		perror("accept");
		printf("client request accepted..\n");

		if(fork()==0)
		{
			client_info();
			while(1)
			{
				read(client_sock,s,sizeof(s));
				if(strcmp(s,"bye")==0)
					break;
				convert_data(s);
				write(client_sock,s,strlen(s)+1);
			}
		}
	}
	close(server_sock);
	close(client_sock);

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
