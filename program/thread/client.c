// msg queue server - client (client)

#include "header.h"
int main(int argc, char **argv)
{

	if(argc!=2)
	{
		printf("usage:- ./client client_id");
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
//////////////////////////////////////////////////////////////////////

	struct sockaddr_in server_id, client_id;
	server_id.sin_family=AF_INET;
	server_id.sin_port=htons(2000);
	server_id.sin_addr.s_addr=inet_addr("127.0.0.1");
	len=sizeof(server_id);
	if(connect(server_sock,(struct sockaddr *)&server_id,len)<0)
	{
		perror("connect");
		return 0;
	}	
	perror("connect");
//////////////////////////////////////////////////////////////////////
// send client id into socket to server.
	int id=atoi(argv[1]);
	printf("client id is-> %d\n",id);
	write(server_sock,&id,sizeof(id));	
	printf("send id...\n\n");
	
	
/////////////////////////////////////////////////////////////////////
	struct msgbuf v;
	key_t key = ftok("logger_key", 65);
	
	int msgid=msgget(key,0664);
	char s[30];
	while(1){
		printf("Enter the string..\n");
		scanf(" %[^\n]",s);
		
		v.mtype=1;
		strcpy(v.data, s);
		v.client_id=id;
		msgsnd(msgid,&v,sizeof(v) - sizeof(long),0);

	
		if(strcmp("byy",v.data)==0)
		{	
			break;
		}
//		msgrcv(msgid,&v,sizeof(v) - sizeof(long),2,0);
//		printf("new string is--> %s\n",s);
	}
	close(server_sock);
}
