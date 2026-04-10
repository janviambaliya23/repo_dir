// QUESTION:- encrypt and decrypt in 1 program.

#include "header.h"

void main()
{
	struct student st;
	unsigned char *plaintext;
	unsigned char key[32],iv[16],ciphertext[1024];
	int len,plen,clen;
//------------------------------------- filling structure + struct -> bytes(raw data - binary data).
	st.id=1;
	st.value=100;
	strcpy(st.msg,"janvi");

	plaintext=(unsigned char *)&st;
	plen=sizeof(st);
//------------------------------------ file oepn
	FILE *fp=fopen("key.bin","rb");
	if(fp==NULL)
	{
		perror("fopen");
		return;
	}

	fread(key,1,32,fp);
	fread(iv,1,16,fp);
	printf("... load key and iv done.... \n");
	fclose(fp);
	printf("key-> %2x \n",key[0]);
        printf("iv-> %2x \n",iv[0]);

//-----------------------------------  encryption

	EVP_CIPHER_CTX *ctx=EVP_CIPHER_CTX_new();

	EVP_EncryptInit_ex(ctx,EVP_aes_256_cbc(),NULL,key,iv);
	EVP_EncryptUpdate(ctx,ciphertext,&len,plaintext,plen);
	clen=len;
	EVP_EncryptFinal_ex(ctx,ciphertext+len,&len);
	clen+=len;

	printf("encrypted msg is->");
	for(int i=0;i<clen;i++)
	{
		printf("%2x ",ciphertext[i]);
	}
	printf("\nDone...\n");
//------------------------------------ decryption

	int dlen,len2;
	unsigned char dplaintext[1024];
	EVP_DecryptInit_ex(ctx,EVP_aes_256_cbc(),NULL,key,iv);
	EVP_DecryptUpdate(ctx,dplaintext,&len2,ciphertext,clen);
	dlen=len2;
	EVP_DecryptFinal_ex(ctx,dplaintext+len2,&len2);
	dlen+=len2;
//-------------------------------------  conver byte -> structure

	struct student st2;
	memcpy(&st2,dplaintext,sizeof(st2));
	printf("id->%d ,value->%d , msg-> %s \n",st2.id,st2.value,st2.msg);
	EVP_CIPHER_CTX_free(ctx);

}
