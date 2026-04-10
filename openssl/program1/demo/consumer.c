#include "header.h"

int flag;//, flush_flag=0;
int ack_fd;
unsigned char key[32],iv[16];
void rand_byte(unsigned char *, int);
void my_isr_handler(int arg)
{
	//	flush_flag=1;
	if(arg == SIGUSR1)
	{
		printf("signal come from transfter...\n");
		printf("inside flush flag..\n");
		write(ack_fd,"done",4);
		printf("ack send to transformer...\n");
		//	flush_flag=0;
	}
	else if(arg == SIGUSR2)
		flag=1;
}
int main()
{
	FILE *fp=fopen("cons_id.txt","a");
	int process_id=getpid();
	printf("process is --> %d\n",process_id);
	fprintf(fp,"%d",process_id);
	fclose(fp);

	////////////////////////////////////////////-- mkfifo	
	int fd=open("myfifo2",O_RDONLY);
	FILE *fout;
	fout=fopen("out.txt","a");

	ack_fd = open("ackfifo",O_RDWR);
	///////////////////////////////////////////////-- rand_byte
	FILE *KEY=fopen("key.bin","rb");
	if(KEY==NULL)
	{
		perror("fopen");
		return 0;
	}
	fread(key,1,32,KEY);
	printf("key--> ");
	rand_byte(key,32);

	fread(iv,1,16,KEY);
	printf("\n\niv--> ");
	rand_byte(iv,16);
	fclose(KEY);
	signal(SIGUSR1,my_isr_handler);
	signal(SIGUSR2,my_isr_handler);


	////////////////////////////////////////////////--  Decryption

	unsigned char ciphertext[1024],dciphertext[1024];
	int dlen,len,clen;
	while(1)
	{
		EVP_CIPHER_CTX *ctx=EVP_CIPHER_CTX_new();

		 if(flag)
                {
                        FILE *KEY=fopen("key.bin","rb");
                        if(KEY==NULL)
                        {
                                perror("fopen");
                                return 0;
                        }
                        fread(key,1,32,KEY);
                        printf("key--> ");
                        rand_byte(key,32);

                        fread(iv,1,16,KEY);
                        printf("\n\niv--> ");
                        rand_byte(iv,16);
                        fclose(KEY);
                        flag=0;
                }



		EVP_DecryptInit_ex(ctx,EVP_aes_256_cbc(),NULL,key,iv);
		int r=read(fd,&clen,sizeof(clen));
		if(r==0)
		{	
			printf("closed FIFO2.....\n");
			break;
		}
		else if(r<0)
		{
			perror("read");
			continue;
		}
		int total=0;
		while(total<clen)
		{
			int n1=read(fd,ciphertext+total, clen-total);
			if(n1<=0)
			{
				perror("read data");
				break;
			}
			total+=n1;
		}
		//printf("elen(c)----> %d\n ",clen);
		EVP_DecryptUpdate(ctx,dciphertext,&len,ciphertext,clen);
		dlen=len;

		if((EVP_DecryptFinal_ex(ctx,dciphertext + len, &len))<=0)
		{
			printf("Decryption failed (wrong key or corrupted data)\n");
			printf("key is--> %x\n",key[0]);
			EVP_CIPHER_CTX_free(ctx);
			continue;
		}
		dlen+=len;

		dciphertext[dlen]='\0';
		static int c=0;
		printf("c=%d\n",c++);
		printf("decryption--> \n%s\n",dciphertext);
			

		//fwrite(dciphertext,1,dlen,fout);
		//	fflush(fout);
		//	printf("data written..\n");
		
		///////////////////////////////////////////--- free everything
		EVP_CIPHER_CTX_free(ctx);
	}
	close(fd);
	fclose(fout);
	return 0;

}
void rand_byte(unsigned char *data, int num)
{
	for(int i=0;i<num;i++)
	{
		printf("%02x ",data[i]);
	}
	printf("\n");
}
