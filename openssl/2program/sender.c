#include "header.h"
int sem_id;

void lock(int);
void unlock(int);

int main()
{
	srand(getpid());
	struct trafficdata st1;
	struct hashentry st2;
	struct sharedmemory *ptr;

	unsigned char key[32],iv[16],ciphertext[1024];
	unsigned char *plaintext;
	int plen,len,clen;

	int index;
	struct tm *time_get;
	//---------------------------------------  share memory
	int shm_id=shmget(50,sizeof(struct sharedmemory),IPC_CREAT|0664);
	if(shm_id<0)
	{
		perror("shmget");
		return 0;
	}

	ptr=(struct sharedmemory *)shmat(shm_id,NULL,0);
	if(ptr==NULL)
	{
		perror("shmat");
		return 0;
	}

	//----------------------------------------  semaphore
	sem_id=semget(51,10,IPC_CREAT|0664);
	if(sem_id>=0)
	{
		for(int i=0;i<10;i++)
			semctl(sem_id,i,SETVAL,1);
	}
	else
	{
		sem_id=semget(51,10,0664);
	}
	//-----------------------------------------  make all id -1
		for(int i=0;i<10;i++)
			ptr->table[i].id=-1;
	
//		for(int i=0;i<10;i++)
//			printf("--> %d\n ",ptr->table[i].id);

	//--------------------------------------- key generate
	FILE *fp=fopen("key.bin","rb");
	if(fp==NULL)
	{
		perror("fopen");
		return 0;
	}
	fread(key,32,1,fp);
	fread(iv,16,1,fp);
	fclose(fp);
	printf("key-> %2x \n",key[0]);
	printf("iv-> %2x \n",iv[0]);
	//--------------------------------------- generat randome data
	while(1)
	{
		st1.density=rand()%100+1;	// 1-100
		st1.speed=rand()%61+20;		// 20-80
		

		time(&st1.time);
		time_get=localtime(&st1.time);
		strftime(st1.buff,sizeof(st1.buff),"%H:%M:%S",time_get);
		int identifier=rand()%50+1;	// 1-50
		//----------------------------------------  bucket index
		
		index=(identifier)%10;
		printf("Index-> %d, Density-> %d, Speed-> %d,  ID-> %d, Time-> %s\n",index,st1.density, st1.speed, identifier,st1.buff);

		plaintext=(unsigned char *)&st1;
		plen=sizeof(st1);
		// --------------------------------------- encryption

		EVP_CIPHER_CTX *ctx=EVP_CIPHER_CTX_new();
		EVP_EncryptInit_ex(ctx,EVP_aes_256_cbc(),NULL,key,iv);
		EVP_EncryptUpdate(ctx,ciphertext,&len,(unsigned char *)plaintext,plen);
		clen=len;
		EVP_EncryptFinal_ex(ctx,ciphertext+len,&len);
		clen+=len;

		//-----------------------------------------  LOCK
		lock(index);

		ptr->table[index].id=identifier;
		memcpy(ptr->table[index].ciphertext,ciphertext,clen);
		ptr->table[index].clen=clen;
		//----------------------------------------  UNLOCK
		unlock(index);
		sleep(1);
	}
}

void lock(int index)
{
	struct sembuf v;
	v.sem_num=index;
	v.sem_flg=0;
	v.sem_op=-1;
	semop(sem_id,&v,1);
}

void unlock(int index)
{
	struct sembuf v;
	v.sem_num=index;
	v.sem_flg=0;
	v.sem_op=1;
	semop(sem_id,&v,1);
}
