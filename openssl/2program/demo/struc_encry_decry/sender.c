// QUESTION:- encryption and decryption with shared memory and structure.

#include"header.h"

void main()
{
	struct student st;
	struct shm_data *ptr;
	unsigned char *plaintext;
	unsigned char ciphertext[1024],key[32],iv[16];
	int len,clen,plen;
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

	semctl(sem_id,0,SETVAL,1);
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
//---------------------------- struct -> bytes
	st.id=1;
	st.value=100;
	strcpy(st.msg,"jaanvi");

	plaintext=(unsigned char *)&st;
	plen=sizeof(st);

//----------------------------- encryption
	
	EVP_CIPHER_CTX *ctx=EVP_CIPHER_CTX_new();
	EVP_EncryptInit_ex(ctx,EVP_aes_256_cbc(),NULL,key,iv);
	EVP_EncryptUpdate(ctx,ciphertext,&len,plaintext,plen);
	clen=len;
	EVP_EncryptFinal_ex(ctx,ciphertext+len, &len);
	clen+=len;

	memcpy(ptr->ciphertext,ciphertext,clen);
	ptr->clen=clen;
	printf("waiting for 5 sec....\n");
	sleep(5);
//---------------------------------------------- UNLOCK
	v.sem_op=1;
	semop(sem_id,&v,1);
	shmdt(ptr);
}
