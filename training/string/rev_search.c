#include<stdio.h>
#include<unistd.h>

int countlen(const char *s)
{
	int c,i;
	for(i=0;s[i];i++);
		return i;
}

void reverse(char *s)
{
	int c=countlen(s),i,j;
	char temp;
	for(i=0,j=c-1;i<j;i++,j--)
	{
		temp=s[i];
		s[i]=s[j];
		s[j]=temp;
	}

}

char *my_strchr(char *s, char c)
{
	int i;
	for(i=0;s[i];i++)
	{
		if(s[i]==c)
			return s+i;
	}
	return NULL;

}

char *my_strrchr(char *s, const char c)
{
	int count=countlen(s),i;
	for(i=count-1;i>=0;i--)
	{
		if(s[i]==c)
			return s+i;
	}
	return 	NULL;
}

void main()
{
	char s[30];
	printf("Enter the string...\n");
	scanf("%[^\n]",s);

	int c=countlen(s);
	printf("length is--> %d\n",c);

	reverse(s);
	printf("reverse string--> %s\n",s);

	char charector;
	printf("\nEnter the new charector...\n");
	scanf(" %c",&charector);
	char *p=my_strchr(s,charector);
	printf("charecter found at -> %p position\n",p);


	char *d=my_strrchr(s,charector);
	printf("charecter found at -> %p position\n",d);
}
