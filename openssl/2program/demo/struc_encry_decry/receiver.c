// QUESTION:- encryption and decryption with shared memory and structure.

#include"header.h"

void main()
{
	struct student st;
	struct shm_data *ptr;
	unsigned char *plaintext,dplaintext[1024];
	unsigned char ciphertext[1024],key[32],iv[16];
	int len,dlen;
	int shm_id=shmget(30,sizeof(struct student),IPC_CREAT|0664);
	if(shm_id<0)
	{
		perror("shmget");
		return;
	}

	
	ptr=(struct shm_data *) shmat(shm_id,NULL,0);
	if(ptr==NULL)
	{
		perror("shmat");
		return;
	}
//--------------------------------------------- semaphore
	int sem_id=semget(31,1,IPC_CREAT|0664);
	if(sem_id<0)
	{
		perror("semget");
		return;
	}

	struct sembuf v;
	v.sem_num=0;
	v.sem_flg=0;

//---------------------------- open file
	FILE *fp=fopen("key.bin","rb");
	if(fp==NULL)
	{
		perror("fopen");
		return;
	}
	fread(key,32,1,fp);
	fread(iv,16,1,fp);
	fclose(fp);
	printf("key-> %2x \n",key[0]);
	printf("iv-> %2x \n",iv[0]);
//----------------------------------------------- LOCK 
	v.sem_op=-1;
	semop(sem_id,&v,1);
	printf("file lock...\n");
	printf("sleep for 2 sec..\n");
	sleep(2);

//----------------------------- encryption
	int clen=ptr->clen;

	memcpy(ciphertext,ptr->ciphertext,sizeof(ciphertext));

	EVP_CIPHER_CTX *ctx=EVP_CIPHER_CTX_new();
	EVP_DecryptInit_ex(ctx,EVP_aes_256_cbc(),NULL,key,iv);
	EVP_DecryptUpdate(ctx,dplaintext,&len,ciphertext,clen);
	dlen=len;

	EVP_DecryptFinal_ex(ctx,dplaintext+len,&len);
	dlen+=len;

	struct student st2;
	memcpy(&st2,dplaintext,sizeof(st2));
	printf("id->%d ,value->%d , msg-> %s \n",st2.id,st2.value,st2.msg);


	printf("done....\n");
//---------------------------------------------- UNLOCK
	v.sem_op=1;
	semop(sem_id,&v,1);
	
	EVP_CIPHER_CTX_free(ctx);
	shmdt(ptr);
	shmctl(shm_id, IPC_RMID, NULL);

}
