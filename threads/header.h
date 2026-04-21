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

struct msgbuf
{
	long mtype;
	int client_id;
	char data[30];
};


struct shmdata
{
	int ary[5];
	int count;

};
