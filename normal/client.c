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
	if(connect(server_sock,(struct sockaddr *)&server_id,len)<0)
	{
		perror("connect");
		return 0;
	}	
	perror("connect");

	char s[30];
		printf("Enter the string..\n");
		scanf(" %[^\n]",s);
		write(server_sock,s,strlen(s)+1);
		read(server_sock,s,sizeof(s));
		printf("new string is--> %s\n",s);
	close(server_sock);
}
