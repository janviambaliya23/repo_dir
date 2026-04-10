#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>


typedef struct queue
{
	int ary[10];
	int front,rear;
}q;

int dequeue(struct queue *q);
void print(struct queue *q);
void enqueue(struct queue *q);
