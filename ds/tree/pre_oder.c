#include "header.h"

static int idx=-1;
int main()
{

	int ary[] = {1,2,-1,-1,3,4,-1,-1,5,-1,-1};

	Node *root_node=buildtree(ary);
/*	printf("%d\n",root_node->data);			//	1
	printf("%d\n",root_node->left->data);		//	2
	printf("%d\n",root_node->right->data);		//	3
*/

//-------------------------------------------- preoder
/*	preoder(root_node);
	printf("\n");
//-------------------------------------------- inoder	
	inoder(root_node);
	printf("\n");
*/
//-------------------------------------------  postoder
	postoder(root_node);
	printf("\n");


	return 0;
}

Node *buildtree(int *data)
{
	idx++;
	if(data[idx]==-1)
		return 	NULL;

	Node *root=creat_node(data[idx]);
	root->left=buildtree(data);
	root->right=buildtree(data);
	return root;
}
Node *creat_node(int value)
{
	Node *node_creat=malloc(sizeof(Node));
	node_creat->data = value;
	node_creat->left=node_creat->right = NULL;
	return node_creat;
}

void preoder(Node *root)
{
	if(root==NULL)
		return;

	printf("%d ",root->data);
	preoder(root->left);
	preoder(root->right);


}

void inoder(Node *root)
{
	if(root==NULL)
		return;

	inoder(root->left);
	printf("%d \n",root->data);
	inoder(root->right);
}

void postoder(Node *root)
{
	if(root==NULL)
		return;

	postoder(root->left);
	postoder(root->right);
	printf("%d ",root->data);
}
