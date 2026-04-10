#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/shm.h>
#include <sys/wait.h>
#include<time.h>
#include<fcntl.h>
#include<sys/ipc.h>
#include<signal.h>
#include<errno.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/sem.h>


typedef struct log
{
	char time[64];
	char msg[50];
	char day[30];

}T;
