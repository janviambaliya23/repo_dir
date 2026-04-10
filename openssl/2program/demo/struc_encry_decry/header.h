#include <sys/shm.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <time.h>


struct student
{
	int id;
	int value;
	char msg[20];
};

struct shm_data
{
	unsigned char ciphertext[1024];
	int clen;
};
