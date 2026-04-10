// basic encryption

#include "header.h"

int main()
{
	unsigned char plaintext[30];
	printf("Enter the data you want to encrypt..\n");
	scanf("%[^\n]",plaintext);

	unsigned char key[32];
	unsigned char iv[16];

	RAND_bytes(key,sizeof(key));
	RAND_bytes(iv,sizeof(iv));

	unsigned char ciphertext[128];

	int len,ciphertext_len;

	EVP_CIPHER_CTX *ctx= EVP_CIPHER_CTX_new();
	EVP_EncryptInit_ex(ctx,EVP_aes_256_cbc(),NULL,key,iv);

	EVP_EncryptUpdate(ctx,ciphertext,&len,plaintext,strlen((char *)plaintext));
	ciphertext_len=len;

	EVP_EncryptFinal_ex(ctx,ciphertext + len,&len);
	ciphertext_len+=len;

	printf("encrypted data..\n");
	for(int i=0;i<ciphertext_len;i++)
	{
		printf("%02x ",ciphertext[i]);
	}
	printf("\n");


}
