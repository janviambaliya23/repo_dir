#include "header.h"
static int idx=-1;
int size;
int main()
{

	int arr[]={50,30,20,-1,-1,40,-1,-1,70,60,-1,-1,80,-1,-1};
	size=sizeof(arr)/sizeof(arr[0]);
	Node *root=buildtree(arr);
	leveloder(root);
	return 0;
}

Node *creat_node(int value)
{
	Node *creat_node=malloc(sizeof(Node));
	creat_node->data=value;
	creat_node->left = creat_node->right = NULL;
	return creat_node;
}

Node * buildtree(int *data)
{
	idx++;
	if(data[idx]==-1)
		return NULL ;
	Node *root=creat_node(data[idx]);
	root->left=buildtree(data);
	root->right=buildtree(data);
	return root;
}

void leveloder(Node *root)
{
	if(root==NULL)
		return;

	struct queue q;
	q.front=q.rear=-1;
	enqueue(&q,root);
	while(q.front !=-1)
	{
		Node *temp=dequeue(&q);
		printf("%d ",temp->data);
		if(temp->left)
			enqueue(&q,temp->left);
		if(temp->right)
			enqueue(&q,temp->right);
	}
}

void enqueue(struct queue *q, Node *n)
{
	if(q->rear==size-1)
	{
		printf("queue is empty..\n");
		return;
	}
	if(q->front==-1)
		q->front=0;

	q->ary[++q->rear]=n;
}

Node *dequeue(struct queue *q)
{
	if(q->front==-1)
	{
		printf("queue is empty...\n");
		return NULL;
	}

	Node *root=q->ary[q->front];
	if(q->front==q->rear)
		q->front = q->rear = -1;
	else
		q->front++;
	return root;
}
