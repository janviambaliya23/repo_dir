#include "header.h"

unsigned char key_old[32], iv_old[16];
unsigned char key_new[32], iv_new[16];

int current_version=1;

void rand_byte(unsigned char *, int);

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

	///////////////////////////////////////////////-- rand_byte

	FILE *KEY=fopen("key.bin","rb");
	if(KEY==NULL)
	{
		perror("fopen");
		return 0;
	}
	
	fread(key_new,1,32,KEY);
	fread(iv_new,1,16,KEY);
	
	memcpy(key_old, key_new, 32);
	memcpy(iv_old, iv_new, 16);
	
	printf("key--> ");
	rand_byte(key_new,32);
	printf("\n\niv--> ");
	rand_byte(iv_new,16);
	
	fclose(KEY);

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

			memcpy(key_old, key_new, 32);
			memcpy(iv_old, iv_new, 16);

			// load new
			fread(key_new,1,32,KEY);
			fread(iv_new,1,16,KEY);
			fclose(KEY);

			printf("key--> ");
			rand_byte(key_new,32);
			printf("\n\niv--> ");
			rand_byte(iv_new,16);
			
			current_version++;
			flag=0;
		}

		int recv_version;

		 int r = read(fd, &recv_version, sizeof(recv_version));	
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

		if(read(fd,&clen,sizeof(clen))<=0)
		{
			perror("read length");
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
		 unsigned char *use_key;
		 unsigned char *use_iv;
		 if(recv_version == current_version)
		 {
			 use_key = key_new;
			 use_iv = iv_new;
		 }
		 else
		 {
			 use_key = key_old;
			 use_iv = iv_old;
		 }
		//printf("elen(c)----> %d\n ",clen);
		EVP_DecryptInit_ex(ctx,EVP_aes_256_cbc(),NULL,use_key,use_iv);
		EVP_DecryptUpdate(ctx,dciphertext,&len,ciphertext,clen);
		dlen=len;
		EVP_DecryptFinal_ex(ctx,dciphertext + len, &len);

		/*
		if((EVP_DecryptFinal_ex(ctx,dciphertext + len, &len))<=0)
		{
			//printf("Decryption failed (wrong key or corrupted data)\n");
			EVP_CIPHER_CTX_free(ctx);
			continue;
		}
*/		dlen+=len;

		dciphertext[dlen]='\0';
		static int c=0;
		printf("c=%d\n",c++);
		printf("\n\ndecryption--> \n%s\n",dciphertext);
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
