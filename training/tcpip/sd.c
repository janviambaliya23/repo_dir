#include "header.h"
int flag=0,i=0;
char files[10][10];

void *client_thread(void *arg)
{

	int client=*(int *)arg;
	printf("client id-> %d\n",client);
	free(arg);
 //----------------------------------
                printf("file creat 1st time...\n");
                int fd1=open("file1.txt",O_RDONLY|O_CREAT,0664);
                int fd2=open("file2.txt",O_RDONLY|O_CREAT,0664);
                int fd3=open("file3.txt",O_RDONLY|O_CREAT,0664);

                for(int i=1;i<4;i++)
                {
                        char copy[10];
                        sprintf(copy,"file%d.txt",i);
                        strcpy(files[i-1],copy);
                }
                write(client,files,sizeof(files));

                int op;
                char ary[100];
                while(1)
                {
                        int n=read(client,ary,sizeof(ary));
                        if(n<=0)
                        {
                                //printf("client terminate...\n");
                                close(client);
                                //continue;
                                return 0;
                        }
                        //------------------------------------------ file check         
                        printf("file is-> %s\n",ary);
			 //----------------------------------------------  file open
                        FILE *fp=fopen(ary,"r");
                        if(fp==NULL)
                        {
                                printf("incorrect file option..\n");
                                return 0;
                        }

                        while(fgets(ary,100,fp))
                        {
                               // printf("%s, len: %ld\n",ary, strlen(ary));
                                write(client,ary,strlen(ary)+1);
                               // printf("writing %ld bytes data...!\n", strlen(ary)+1);
                                sleep(1);
                        }
                        write(client, "END", 4);
                        printf("sending done....\n");
                        fclose(fp);
                }

	return NULL;
}


int check(char *);
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
	if(bind(server_socket_id,(struct sockaddr *)&server_id,len)<0)
	{
		perror("bind");
		return 0;
	}
	perror("bind");
	//-----------------------------------
	if(listen(server_socket_id,5)<0)
	{
		perror("listen");
		return 0;
	}
	perror("listen");
	//-----------------------------------

	while(1)
	{
		client_socket=accept(server_socket_id,(struct sockaddr *)&client_id,&len);
		if(client_socket<0)
		{
			perror("accept");
			return 0;
		}
		perror("accept");
		
		int *pclient = malloc(sizeof(int));
                *pclient=client_socket;
	
		printf("client socket id in main...%d\n",client_socket);
		pthread_t th;
		pthread_create(&th,0,client_thread,pclient);
		
		pthread_detach(th);
	
	}
	close(server_socket_id);
}

