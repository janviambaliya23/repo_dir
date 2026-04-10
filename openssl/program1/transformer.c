#include "header.h"

#define size 5
static int top=-1;
char que[size][1024];
int qlen[size];
int fd,fd2;
int clen;
pthread_mutex_t lock;
pthread_cond_t cond;
pthread_mutex_t key_lock;

unsigned char key[32],iv[16];

void rand_byte(unsigned char *, int);
void enqueue(char *,int);
int dequeue(char *,int *);
int encryption(unsigned char *,int,unsigned char *,unsigned char *,unsigned char *);
int decryption(unsigned char *,int,unsigned char *,unsigned char *,unsigned char *);
void load_key();



void isr_handler(int n)
{
	printf("signal evock..\n");
	load_key();
}

void *worker_thread(void *arg)
{
	unsigned char plaintext[1024],ciphertext[1040];
	unsigned char local_key[32],local_iv[16];
	int elen,dlen,clen;
	while(1)
	{
		if(dequeue((char *)ciphertext,&clen))
		{

			pthread_mutex_lock(&key_lock);
			memcpy(local_key,key,32);
			memcpy(local_iv,iv,16);
			pthread_mutex_unlock(&key_lock);


			dlen=decryption(ciphertext,clen,local_key,local_iv,plaintext);
			plaintext[dlen]='\0';
		//	printf("data-> %s\n",plaintext);
		static int c=0;
	                printf("c=%d\n",c++);
			printf("data-> %.*s\n",dlen,plaintext);
			// modify()
			elen=encryption(plaintext,dlen,local_key,local_iv,ciphertext);
			printf("key->%02x\n",key[0]);
			pthread_mutex_lock(&lock);
			write(fd2,&elen,sizeof(elen));
			write(fd2,ciphertext,elen);
			pthread_mutex_unlock(&lock);
		}
	}
	return NULL;
}

int main()
{
	printf("pid=%d\n\n",getpid());
	char buff[1024];
	////////////////////////////////////////-- mkfifo
	mkfifo("myfifo2",0664);
	fd=open("myfifo",O_RDONLY);
	fd2=open("myfifo2",O_WRONLY);

	///////////////////////////////////////////--- signal
	signal(SIGUSR1,isr_handler);

	pthread_t th[4];
	pthread_mutex_init(&lock,NULL);
	pthread_cond_init(&cond,NULL);
	pthread_mutex_init(&key_lock,NULL);
	
	///////////////////////////////////////////////-- rand_byte
	pthread_mutex_lock(&lock);
	FILE *key1=fopen("key.bin","rb");
	if(key1==NULL)
	{
		perror("fopen");
		return 0;
	}
	fread(key,1,32,key1);
	printf("key--> ");
	rand_byte(key,32);

	fread(iv,1,16,key1);
	printf("\n\niv--> ");
	rand_byte(iv,16);
	fclose(key1);
	pthread_mutex_unlock(&lock);
	/////////////////////////////////////////////////


	for(int i=0;i<4;i++)
		pthread_create(&th[i],NULL,&worker_thread,NULL);

	while(1)
	{
		int clen;
		if(read(fd,&clen,sizeof(clen))<=0)
			break;

		read(fd,buff,clen);
		enqueue(buff,clen);
	}

	for(int i=0;i<4;i++)
		pthread_join(th[i],NULL);
	///////////////////////////////////////////--- free everything
	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&key_lock);
	close(fd);
	close(fd2);
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
void enqueue(char *data,int len)
{
	pthread_mutex_lock(&lock);
	if(top>=size-1)
	{
		printf("stack is overflow..\n");
		pthread_mutex_unlock(&lock);
		return;
	}
	top++;
	memcpy(que[top],data,len);
	qlen[top]=len;
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&lock);
}
int dequeue(char *data,int *len)
{
	pthread_mutex_lock(&lock);
	while(top<=-1)
	{
		printf("queue is empty..\n");
		pthread_cond_wait(&cond,&lock);
	}
	//	strcpy(data,que[top]);
	memcpy(data,que[top],qlen[top]);
	*len=qlen[top];
	for(int i=0;i<top;i++)
	{
		memcpy(que[i],que[i+1],qlen[i+1]);
		qlen[i]=qlen[i+1];
		//		strcpy(que[i],que[i+1]);
	}
	top--;
	pthread_mutex_unlock(&lock);
	return 1;
}

int encryption(unsigned char *plaintext,int plen,unsigned char *key,unsigned char *iv,unsigned char *ciphertext)
{

	int ciphertext_len,len;
	EVP_CIPHER_CTX *ctx=EVP_CIPHER_CTX_new();

	EVP_EncryptInit_ex(ctx,EVP_aes_256_cbc(),NULL,key,iv);
	EVP_EncryptUpdate(ctx,ciphertext,&len,plaintext,plen);
	ciphertext_len=len;

	EVP_EncryptFinal_ex(ctx,ciphertext+len,&len);
	ciphertext_len+=len;
	EVP_CIPHER_CTX_free(ctx);
	return ciphertext_len;
}

int decryption(unsigned char *ciphertext,int clen,unsigned char *key,unsigned char *iv,unsigned char *plaintext)
{
	int plen,len;
	EVP_CIPHER_CTX *ctx=EVP_CIPHER_CTX_new();

	EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

	EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, clen);
	plen = len;

	EVP_DecryptFinal_ex(ctx, plaintext + len, &len);
	plen += len;
	EVP_CIPHER_CTX_free(ctx);
	return plen;
}

void load_key()
{
	unsigned char key[32],iv[16];
	FILE *key1=fopen("key.bin","rb");
	if(key1==NULL)
	{
		perror("fopen");
		return;
	}

	pthread_mutex_lock(&key_lock);
	fread(key,1,32,key1);
	fread(iv,1,16,key1);
	pthread_mutex_unlock(&key_lock);

	printf("key--> ");
	rand_byte(key,32);

	printf("\n\niv--> ");
	rand_byte(iv,16);

	fclose(key1);
}

