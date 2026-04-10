#include "header.h"

#define GREEN  "\033[33m"
#define RESET  "\033[0m"

int  threshold =90;
int time_limit =5;

int sem_id;

void lock(int);
void unlock(int);

void *alert_thread(void *arg)
{
	struct alert_data *st=(struct alert_data *)arg;
	int id=st->ID;
	int density=st->DENSITY;
	printf("\033[31m"); 
	printf("Temprature is above 90 at intersection of %d\nthe density is->%d\n",id,density);
	printf("\033[0m"); 
	return NULL;

}

void my_isr(int n)
{
	FILE *fp=fopen("input.txt","r");
	if(fp==NULL)
	{
		perror("fopen");
		return;
	}
	fscanf(fp,"%d", &threshold);
	fscanf(fp,"%d", &time_limit);
	fclose(fp);
	printf("\n\nnew threashold --> %d and new time_limit --> %d\n",threshold, time_limit);
}

int main()
{
	printf("pid--> %d\n",getpid());
	printf("old threashold --> %d and new time_limit --> %d\n",threshold, time_limit);

	struct trafficdata st1;
        struct hashentry st2;
        struct sharedmemory *ptr;

	unsigned char key[32],iv[16],ciphertext[1024],plaintext[1024];
	int identifier,clen,len,dlen;
	time_t cur_time,delay_time;

	pthread_t th;
	signal(SIGHUP,my_isr);
//---------------------------------------  share memory
	int shm_id=shmget(50,sizeof(struct sharedmemory),IPC_CREAT|0664);
	if(shm_id<0)
	{
		perror("shmget");
		return 0;
	}

	ptr=(struct  sharedmemory*)shmat(shm_id,NULL,0);
	if(ptr==NULL)
	{
		perror("shmat");
		return 0;
	}

//----------------------------------------  semaphore
	
	sem_id=semget(51,10,IPC_CREAT|0664);
	if(sem_id<0)
	{
		perror("semget");
		return 0;
	}
	
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

	while(1)
	{
		for(int i=0;i<10;i++)
		{
		sleep(1);
//----------------------------------------  LOCK and copy data from memory
			lock(i);
			identifier=ptr->table[i].id;
			memcpy(ciphertext,ptr->table[i].ciphertext,sizeof(ciphertext));
			clen=ptr->table[i].clen;
//----------------------------------------  UNLOCK
			unlock(i);
			if(identifier==-1)
			{
				printf("skipping...-> %d cause identifier is -> %d\n",i,identifier);
				continue;	
			}
			else
			{
			//-------------------------------- Decrypt data
			EVP_CIPHER_CTX *ctx=EVP_CIPHER_CTX_new();
			EVP_DecryptInit_ex(ctx,EVP_aes_256_cbc(),NULL,key,iv);
			EVP_DecryptUpdate(ctx,plaintext,&len,ciphertext,clen);
			dlen=len;
			EVP_DecryptFinal_ex(ctx,plaintext+len,&len);
			dlen+=len;

			memcpy(&st1,plaintext,sizeof(st1));
 			printf("Index-> %d, Density-> %d, Speed-> %d,  ID-> %d, Time-> %s\n",i,st1.density, st1.speed, identifier,st1.buff);
				time(&cur_time);
				delay_time=st1.time;
				double diff_time=difftime(cur_time,delay_time);
				if(diff_time>=time_limit)
				{
					printf(GREEN);
					printf( "skip cause time diff is--> %f\n",diff_time);
					printf(RESET);
					continue;
				}
				else
				{
					if(st1.density>threshold)
					{
						struct alert_data *ptr2=malloc(sizeof(struct alert_data));
						ptr2->ID=identifier;
						ptr2->DENSITY=st1.density;

						pthread_create(&th,0,alert_thread,ptr2);

						pthread_detach(th);
					}
				}		
			}

		}
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

