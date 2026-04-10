#include "header.h"

volatile int producer_pause=0;
int gpid;

void load_key();
void rand_byte(unsigned char *, int);

void my_handler(int arg)
{
	if(arg==SIGUSR2)
	{
		producer_pause=1;
	}
	else if(arg==SIGUSR1)
	{
		producer_pause=0;
	}
}

int main()
{
	gpid=getpid();
	printf("pid is--> %d\n",gpid);
	FILE *fp1=fopen("cons_id.txt","w");
	fprintf(fp1,"%d\n",gpid);
	fclose(fp1);
	/////////////////////////////////////---  MKFIFO
	mkfifo("myfifo",0664);
	int fd=open("myfifo",O_WRONLY);
	perror("mkfifo");
	/////////////////////////////////////--- rand byte
	unsigned char key[32],iv[16];
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

	signal(SIGUSR2,my_handler);
	signal(SIGUSR1,my_handler);
	////////////////////////////////////---  FILE
	FILE *fp=fopen("input.txt","rb");
	while(1)
	{
		if(producer_pause)
		{
			printf("Producer paused...\n");
			sleep(1);
			continue;
		}
		rewind(fp);
		////////////////////////////////////////////--- ENcryption
		sleep(5);
		unsigned char plaintext[1024],ciphertext[1040];
		int plen,clen,len;

		EVP_CIPHER_CTX *ctx=EVP_CIPHER_CTX_new();
		plen=fread(plaintext,1,1024,fp);

		EVP_EncryptInit_ex(ctx,EVP_aes_256_cbc(),NULL,key,iv);
		EVP_EncryptUpdate(ctx,ciphertext,&len,plaintext,plen);
		clen=len;
		EVP_EncryptFinal_ex(ctx,ciphertext+len,&len);
		clen+=len;

		write(fd,&clen,sizeof(clen));
		write(fd,ciphertext,clen);
		///////////////////////////////////////////--- free everything
		EVP_CIPHER_CTX_free(ctx);
	}
	close(fd);
	fclose(fp);
	return 0;

}
/////////////////--- function
void rand_byte(unsigned char *data, int num)
{
	for(int i=0;i<num;i++)
		printf("%02x ",data[i]);
	printf("\n");
}
