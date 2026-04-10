#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>


typedef struct node
{
	int data;
	struct node *left;
	struct node *right;

}Node;

struct queue
{
	Node *ary[50];
	int front,rear;
};

Node *buildtree(int *);
Node *creat_node(int );
void preoder(Node *);
void inoder(Node *root);
void postoder(Node *root);
void leveloder(Node *root);

void enqueue(struct queue *q, Node *n);
Node *dequeue(struct queue *q);

