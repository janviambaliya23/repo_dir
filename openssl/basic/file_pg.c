// encryption from file.
#include"header.h"

int main()
{
	FILE *in,*out;

	unsigned char key[32];
	unsigned char iv[16];

	RAND_bytes(key,sizeof(key));
	RAND_bytes(iv,sizeof(iv));

	unsigned char inbuf[1024];
	unsigned char outbuf[1040];

	int inlen, outlen;

	in=fopen("input.txt","rb");
	out=fopen("output.enc","wb");

	EVP_CIPHER_CTX *ctx=EVP_CIPHER_CTX_new();

	int size=EVP_EncryptInit_ex(ctx,EVP_aes_256_cbc(),NULL,key,iv);
	while((inlen=fread(inbuf,1,1024,in))>0)
	{
		EVP_EncryptUpdate(ctx,outbuf,&outlen,inbuf,inlen);
		fwrite(outbuf,1,outlen,out);
	}

	EVP_EncryptFinal_ex(ctx,outbuf,&outlen);
	fwrite(outbuf,1,outlen,out);

	EVP_CIPHER_CTX_free(ctx);
	fclose(in);
	fclose(out);
}
