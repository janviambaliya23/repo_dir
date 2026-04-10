#include "header.h"

#define size 2
static int top=-1;
char que[size][1024];
int qlen[size];
int fd,fd2;
int clen;
pthread_mutex_t lock;
pthread_cond_t cond;
pthread_mutex_t key_lock;

unsigned char key[32],iv[16],l_key[32],l_iv[16];

int active_worker =0;

void rand_byte(unsigned char *, int);
void enqueue(char *,int);
int dequeue(char *,int *);
int encryption(unsigned char *,int,unsigned char *,unsigned char *,unsigned char *);
int decryption(unsigned char *,int,unsigned char *,unsigned char *,unsigned char *);
void load_key();



void isr_handler(int n)
{
        FILE *fp;
        int consu_pid,pro_id;
        printf("\n\nsignal evock from handler..\n\n");

        fp=fopen("cons_id.txt","r");
        fscanf(fp,"%d",&pro_id);
        fscanf(fp,"%d",&consu_pid);
        printf("ppid-> %d\n",pro_id);
        printf("gpid-> %d\n",consu_pid);
        fclose(fp);

        kill(pro_id,SIGUSR2);   // stop producer
        while(1)
        {
                pthread_mutex_lock(&lock);
                int queue_empty= (top==-1);
                int worker_busy= (active_worker !=0);
                pthread_mutex_unlock(&lock);

                if(queue_empty && !worker_busy)
                {
                        sleep(1);
                        break;
                }

                printf("Waiting queue to empty before key switch...\n");
                sleep(1);
        }

        load_key();

        sleep(1);
        kill(consu_pid,SIGUSR1);        // notify consumer
        kill(pro_id,SIGUSR1);   // continue producer
}

void *worker_thread(void *arg)
{


        unsigned char plaintext[1024],ciphertext[1040];
        unsigned char t_key[32],t_iv[16];
        int elen,dlen,clen;
        while(1)
        {
                if(dequeue((char *)ciphertext,&clen))
                {

                        pthread_mutex_lock(&lock);
                        active_worker++;
                        pthread_mutex_unlock(&lock);

                        pthread_mutex_lock(&key_lock);
                        memcpy(t_key,l_key,32);
                        memcpy(t_iv,l_iv,16);
                        pthread_mutex_unlock(&key_lock);


                        dlen=decryption(ciphertext,clen,key,iv,plaintext);
                        if(dlen<0)
                        {
                                printf("descryption fail in transformation thread..\n");
                                pthread_mutex_lock(&lock);
                                active_worker--;
                                pthread_mutex_unlock(&lock);
                                continue;
                        }
                        plaintext[dlen]='\0';
                        // modify()

                        elen=encryption(plaintext,dlen,t_key,t_iv,ciphertext);

                        pthread_mutex_lock(&lock);
                        static int c=0;
                        printf("\n\ncount=%d\n",c++);
                        printf("decrypted data-> %.*s\n",dlen,plaintext);
                        printf("encrypted data-> %s\n",ciphertext);
                        pthread_mutex_unlock(&lock);

                        pthread_mutex_lock(&lock);
                        write(fd2,&elen,sizeof(elen));
                        write(fd2,ciphertext,elen);
                        active_worker--;
                        pthread_mutex_unlock(&lock);
                }
        }
        return NULL;
}
int main()
{
//setbuf(stdout, NULL);
        printf("pid=%d\n\n",getpid());
        char buff[1024];
        ////////////////////////////////////////-- mkfifo
        mkfifo("myfifo2",0664);
        fd=open("myfifo",O_RDONLY);
        fd2=open("myfifo2",O_WRONLY);

        ///////////////////////////////////////////--- signal
        signal(SIGUSR1,isr_handler);

        pthread_t th[2];
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
        printf("\niv--> ");
        rand_byte(iv,16);

        memcpy(l_key, key, 32);
        memcpy(l_iv, iv, 16);

        pthread_mutex_unlock(&lock);
        /////////////////////////////////////////////////

        for(int i=0;i<2;i++)
        {
                pthread_create(&th[i],NULL,&worker_thread,NULL);
        }
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
        while(top>=size-1)
        {
                pthread_cond_wait(&cond,&lock);
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
        //      printf("queue is empty..\n");
                pthread_cond_wait(&cond,&lock);
        }
        //      strcpy(data,que[top]);
        memcpy(data,que[top],qlen[top]);
        *len=qlen[top];
        for(int i=0;i<top;i++)
        {
                memcpy(que[i],que[i+1],qlen[i+1]);
                qlen[i]=qlen[i+1];
                //              strcpy(que[i],que[i+1]);
        }
        top--;
        pthread_cond_signal(&cond);
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

        if(EVP_DecryptFinal_ex(ctx, plaintext + len, &len)<=0)
        {
                EVP_CIPHER_CTX_free(ctx);
                return -1;
        }
        plen += len;
        EVP_CIPHER_CTX_free(ctx);
        return plen;
}

void load_key()
{
        unsigned char temp_key[32], temp_iv[16];
        FILE *key1=fopen("key.bin","rb");
        if(key1==NULL)
        {
                perror("fopen");
                return;
        }

        fread(temp_key,1,32,key1);
        fread(temp_iv,1,16,key1);

        pthread_mutex_lock(&key_lock);
        memcpy(l_key,temp_key,32);
        memcpy(l_iv,temp_iv,16);
        pthread_mutex_unlock(&key_lock);

        printf("\n\nnew key--> ");
        rand_byte(l_key,32);

        printf("\n new iv--> ");
        rand_byte(l_iv,16);

        fclose(key1);
}

