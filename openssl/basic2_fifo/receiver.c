#include "header.h"

void main()
{
	unsigned char ciphertext[1024],dciphertext[1024];

//////////////////////////////////// FIFO
	mkfifo("myfifo",0664);
	perror("mkfifo");

	int fd=open("myfifo",O_RDONLY);

////////////////////////////////////  key - IV
	unsigned char key[32];
	unsigned char iv[16];

	read(fd,key,32);
	read(fd,iv,16);
printf("key-> %02x, iv-> %02x\n",key[0],iv[0]);
/////////////////////////////////  Decryption
	
	int dlen,len,clen;

	EVP_CIPHER_CTX *ctx=EVP_CIPHER_CTX_new();
	
	EVP_DecryptInit_ex(ctx,EVP_aes_256_cbc(),NULL,key,iv);
	
	
//	while(read(fd,&clen,sizeof(clen))>0)
//	{
		read(fd,&clen,sizeof(clen));
		read(fd,ciphertext,clen);
		EVP_DecryptUpdate(ctx,dciphertext,&len,ciphertext,clen);
		dlen=len;
//	}

	EVP_DecryptFinal_ex(ctx,dciphertext + len, &len);
	dlen+=len;

	EVP_CIPHER_CTX_free(ctx);
	dciphertext[dlen]='\0';
	printf("decryption--> %s\n",dciphertext);
}
