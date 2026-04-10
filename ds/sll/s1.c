#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

typedef struct student
{
	int rollno;
	char name[20];
	float marks;	
	struct student *next;
}SLL;

void add_node(SLL **);
void print_node(SLL *);
void revers_link(SLL **);
int count_node(SLL *);
void delet_all(SLL **);
void search_node(SLL *);
void print_middle_node(SLL *);
void delet_node(SLL **);


int main()
{
	int op;
	SLL *headptr;
	while(1)
	{
		printf("1->Add node ,2-> Print node ,3->Revers link ,4->Exit ,5-> count node ,6-> delete all node ,7-> search node(by roll_no or name) ,8-> find middle node ,9-> delete node\n");
		scanf("%d",&op);
		switch(op)
		{
			case 1: add_node(&headptr); break;
			case 2: print_node(headptr); break;
			case 3: revers_link(&headptr); break;
			case 4:	exit(0); break;
			case 5: int n=count_node(headptr);
			       printf("\n\nNode is=%d\n",n);	break;
			case 6: delet_all(&headptr); break;
			case 7: search_node(headptr); break;
			case 8: print_middle_node(headptr); break;
			case 9: delet_node(&headptr); break;
			defualt: printf("UNKNOWN OPTION\n"); break;
		}
	}
}

void add_node(SLL **ptr)
{
	SLL *new=malloc(sizeof(SLL));
	new->next=0;
	printf("\nEnter the roll no, name and marks..\n");
	scanf("%d %s %f",&new->rollno, new->name, &new->marks);
	if(*ptr==0)
	{
		*ptr=new;
	}
	else
	{
		SLL *last=*ptr;
		while(last->next!=0)
			last=last->next;
		last->next=new;
	}
}

void print_node(SLL *ptr)
{
	if(ptr!=0)
	{
		printf("\n\n");
		while(ptr)
		{
			printf("%d %s %f\n",ptr->rollno,ptr->name,ptr->marks);
			ptr=ptr->next;
		}
		printf("\n");
	}
	else
		printf("\nNo record found...\n");
}

int count_node(SLL *ptr)
{
	if(ptr==0)
	{
		printf("No record found..\n");
		return 0;
	}
	int c=0;
	while(ptr)
	{
		c++;
		ptr=ptr->next;
	}
	return c;
}

void revers_link(SLL **ptr)
{
	if(*ptr==0)
	{
		printf("No record found..\n");
		return;
	}	
	int c=count_node(*ptr),i=0;
	if(c>1)
	{
		SLL **arr, *t=*ptr;
		arr=malloc(sizeof(SLL *)*c);
		while(t)
		{
			arr[i]=t;
			t=t->next;
			i++;
		}

		for(int i=1;i<c;i++)
			arr[i]->next=arr[i-1];

		*ptr=arr[c-1];
		arr[0]->next=0;
	}
}


void delet_all(SLL **ptr)
{
	if(*ptr==0)
	{
		printf("No record found..\n");
		return;
	}
	SLL *t=*ptr;
	while(t)
	{
		free(t);
		t=t->next;
	}	
	*ptr=0;

}

void search_node(SLL *ptr)
{
	int op;
	printf("1:- find by roll number, 2:- find by name");
	scanf("%d",&op);

	switch(op)
	{
		case 1:
			int n;
			printf("Enter the rollno\n");
			scanf("%d",&n);

			SLL *last=ptr;
			while(last)
			{
				if(last->rollno == n)
				{
					printf("%d %s %f\n",last->rollno, last->name, last->marks);
					return;
				}
				last=last->next;
			}
			printf("No record found..\n");
			break;
		case 2:
			char n1[20];
			printf("Enter the name..\n");
			scanf("%s",n1);

			SLL *last1=ptr;
			while(last1)
			{
				if(strcmp(last1->name, n1)==0)
				{
					printf("%d %s %f\n",last1->rollno, last1->name, last1->marks);
					return;
				}
				last1=last1->next;
			}
			printf("No record found..\n");

			break;
	}
}

void print_middle_node(SLL *ptr)
{
	int c=count_node(ptr);
	int middle=c/2;
	SLL *last=ptr;
	for(int i=0;i<middle;i++)
		last=last->next;
	printf("%d %s %f\n", last->rollno, last->name,last->marks);
}

void delet_node(SLL **ptr)
{
	if(*ptr==0)
	{
		printf("No record found..\n");
		return;
	}

	int n;
	SLL *last=*ptr,*prev;
	printf("Enter the node you want to delete..\n");
	scanf("%d",&n);

	while(last)
	{
		if(last->rollno == n)
		{
			if(last==*ptr)
				*ptr=last->next;
			else
				prev->next=last->next;

		free(last);		
		return;
		}
		prev=last;
		last=last->next;
	}
	printf("node does not found..\n");
}
