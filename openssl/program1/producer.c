#include "header.h"

void load_key();
void rand_byte(unsigned char *, int);

int main()
{

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
		
	////////////////////////////////////---  FILE
	while(1)
	{
		FILE *fp=fopen("input.txt","rb");

		////////////////////////////////////////////--- ENcryption

		unsigned char plaintext[1024],ciphertext[1040];
		int plen,clen,len;

		EVP_CIPHER_CTX *ctx=EVP_CIPHER_CTX_new();


		EVP_EncryptInit_ex(ctx,EVP_aes_256_cbc(),NULL,key,iv);

		while((plen=fread(plaintext,1,1024,fp))>0)
		{
			if(plen<=0)
				break;
			EVP_EncryptUpdate(ctx,ciphertext,&len,plaintext,plen);
			clen=len;
			write(fd,&clen,sizeof(clen));
			write(fd,ciphertext,clen);
		}
		EVP_EncryptFinal_ex(ctx,ciphertext+len,&len);
		clen+=len;
		write(fd,&clen,sizeof(clen));
                write(fd,ciphertext,clen);


		///////////////////////////////////////////--- free everything
		EVP_CIPHER_CTX_free(ctx);
		fclose(fp);
	sleep(3);
	}
		close(fd);
		return 0;
	
}
/////////////////--- function
void rand_byte(unsigned char *data, int num)
{
	for(int i=0;i<num;i++)
		printf("%02x ",data[i]);
	printf("\n");
}

