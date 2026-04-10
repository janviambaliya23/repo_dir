#include<stdio.h>
#include<unistd.h>

int countlen(const char *s)
{
	int c,i;
	for(i=0;s[i];i++);
		return i;
}

int my_strcmp(const char *s, const char *d)
{
	while(*s==*d)
	{
		if(*s=='\0')
			return 0;
		s++;
		d++;
	}
	return (*s-*d);
}

int my_strncmp(char *s, char *d,int c)
{
	int i=0;
	while(*s==*d)
	{
		if(*s=='\0')
			return 0;
		else if(i==c)
		{	
		//	break;
			return 0;
		}
		i++;
		s++;
		d++;
	}
	return (*s-*d);
}

void main()
{
	char s[30];
	char d[50];
	printf("Enter the string...\n");
	scanf("%[^\n]",s);

	int c=countlen(s);
	printf("length is--> %d\n",c);
	
	int num;
	printf("Enter how many number you want to copy..\n");
	scanf(" %d",&num);

	printf("\n\nEnter new string..\n");
	scanf(" %[^\n]",d);

	int a1=my_strcmp(s,d);
	if(a1==0)
	{
		printf("both string are equal...\n");
	}
	else
		printf("both string are not equal..\n");
	
	int a2=my_strncmp(s,d,num);
	if(a2==0)
	{
		printf("both string are equal by count...\n");
	}
	else
		printf("both string are not equal by count..\n");
}
