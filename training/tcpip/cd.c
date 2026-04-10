#include "header.h"

int file_exist(char *name)
{
	FILE *fp=fopen(name,"r");
	if(fp)
	{
		fclose(fp);
		return 1;
	}
	return 0;
}
int main()
{
	int server_socket_id,client_socket;
	server_socket_id=socket(AF_INET,SOCK_STREAM,0);
	if(server_socket_id<0)
	{
		perror("socket");
		return 0;
	}
	perror("socket");
	//----------------------------------
	struct sockaddr_in server_id,client_id;
	server_id.sin_family=AF_INET;
	server_id.sin_port=htons(3000);
	server_id.sin_addr.s_addr=inet_addr("0.0.0.0");
	int len=sizeof(server_id);
	if(connect(server_socket_id,(struct sockaddr *)&server_id,len)<0)
	{
		perror("connect");
		return 0;
	}
	perror("connect");
	//----------------------------------- read 2d array - files
	char files[10][10],filename[100];
	read(server_socket_id, files, sizeof(files));

	int op,i=0;
	while(1)
	{
		printf("you have total this much of file in folder\ntell me which file you want\n");	
		for(int j=0;j<3;j++)
			printf("%d --> %s\n",j,files[j]);

		printf("Enter file name you want to read..\n");
		scanf(" %[^\n]",filename);	// scan filename
		write(server_socket_id,filename,strlen(filename)+1);	// passing file name to server
		
		char base[256],ext[64];
		char newfile[1024];
		char *dot=strrchr(filename,'.');

		if(dot)
		{
			int len=dot-filename;
			strncpy(base,filename,len);
			base[len]='\0';
			strcpy(ext,dot);
		}else{
			strcpy(base,filename);
			ext[0]='\0';
		}
		snprintf(newfile,sizeof(newfile),"%s%s",base,ext);

		int counter=1;
		while(file_exist(newfile))
		{
			snprintf(newfile,sizeof(newfile),"%s_%d%s",base,counter++,ext);
		}
		
		printf("file name-> %s\n",newfile);
		FILE *fp=fopen(newfile,"a+");
		char s[100];
		while(1)
		{
			int n=read(server_socket_id,s,sizeof(s));
			printf("n->%d\n",n);
			s[n] = '\0';

			if(strcmp(s ,"END") == 0 ){
				printf("END\n");
				fclose(fp);
				break ; 
			}
			else{
				printf("%s\n", s);
				fputs(s,fp);
			//	write(1,s,n);
			}
			sleep(1);
		}
	}
	close(server_socket_id);
}
