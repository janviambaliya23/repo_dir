#include "header.h"

void main()
{
	unsigned char plaintext[1024],ciphertext[1024];
	printf("Enter the data..\n");
	scanf("%[^\n]",plaintext);
////////////////////////////////  FIFO
	mkfifo("myfifo",0664);
	perror("mkfifo");

	int fd=open("myfifo",O_WRONLY);

///////////////////////////////   key - IV
	unsigned char key[32];
	unsigned char iv[16];
	RAND_bytes(key,32);
	RAND_bytes(iv,16);

	write(fd,key,32);
	write(fd,iv,16);
	printf("key-> %02x, iv-> %02x\n",key[0],iv[0]);
////////////////////////////////  encryption
	int ciphertext_len,len;
	EVP_CIPHER_CTX *ctx=EVP_CIPHER_CTX_new();

	EVP_EncryptInit_ex(ctx,EVP_aes_256_cbc(),NULL,key,iv);
	EVP_EncryptUpdate(ctx,ciphertext,&len,plaintext,strlen((char *)plaintext));
	ciphertext_len=len;
//	write(fd,&ciphertext_len,sizeof(ciphertext_len));
//	write(fd,ciphertext,ciphertext_len);
	
	EVP_EncryptFinal_ex(ctx,ciphertext+len,&len);
	ciphertext_len+=len;
	write(fd,&ciphertext_len,sizeof(ciphertext_len));
	write(fd,ciphertext,ciphertext_len);

	for(int i = 0; i < ciphertext_len; i++)
       		 printf("%02x ", ciphertext[i]);
       	printf("\n");
	EVP_CIPHER_CTX_free(ctx);	
}
