#include "header.h"

void rand_byte(unsigned char *, int);
int main()
{


	////////////////////////////////////////////-- mkfifo	
	int fd=open("myfifo2",O_RDONLY);
	//	int fd=open("myfifo",O_RDWR);
	FILE *fout;
	fout=fopen("out.txt","a");

		///////////////////////////////////////////////-- rand_byte
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

		////////////////////////////////////////////////--  Decryption

	while(1)
	{
		unsigned char ciphertext[1024],dciphertext[1024];
		int dlen,len,clen;

		EVP_CIPHER_CTX *ctx=EVP_CIPHER_CTX_new();

		EVP_DecryptInit_ex(ctx,EVP_aes_256_cbc(),NULL,key,iv);

		read(fd,&clen,sizeof(clen));
		read(fd,ciphertext,clen);
		EVP_DecryptUpdate(ctx,dciphertext,&len,ciphertext,clen);
		dlen=len;

		EVP_DecryptFinal_ex(ctx,dciphertext + len, &len);
		dlen+=len;

		dciphertext[dlen]='\0';
		static int c=0;
		printf("c=%d\n",c++);
		printf("key->%02x\n",key[0]);
		printf("\n\ndecryption--> \n%s\n",dciphertext);
		fwrite(dciphertext,1,dlen,fout);
		fflush(fout);
		printf("data written..\n");

		///////////////////////////////////////////--- free everything
		EVP_CIPHER_CTX_free(ctx);
	sleep(3);
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
