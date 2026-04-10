#include<stdio.h>
#include<unistd.h>

int countlen(const char *s)
{
	int c,i;
	for(i=0;s[i];i++);
		return i;
}
void my_strcpy(char *d,const char *s)
{
	int i;
	for(i=0;s[i];i++)
	{
		d[i]=s[i];
	}
}

void my_strncpy(char *d,const char *s,int c)
{
	int i;
	for(i=0;i<c;i++)
	{
		d[i]=s[i];
	}
	d[i]='\0';
}
char *my_strstr(char *s, char *c)
{
	int i,j;
	for(i=0;s[i];i++)
	{
		for(j=0;c[j];j++)
			if(s[i+j]!=c[j])
				break;
		if(c[j]=='\0')
			return s+i;
	}
	return NULL;

}

void main()
{
	char s[30];
	printf("Enter the string...\n");
	scanf("%[^\n]",s);

	int c=countlen(s);
	printf("length is--> %d\n",c);
	
	char d[50];
	my_strcpy(d,s);
	printf("destination string --> %s\n",d);


	int num;
	printf("Enter how many number you want to copy..\n");
	scanf(" %d",&num);
	my_strncpy(d,s,num);
	printf("destination string --> %s\n",d);



	char ch[20];
	printf("\n\n\n\nEnter the string you want to find...\n");
	scanf(" %[^\n]",ch);
	char *p=my_strstr(s,ch);
	if(p!=NULL)
	{
		printf("sun string found at %p\n",p);
	}
	else
		printf("sub-string not found..\n");

}
