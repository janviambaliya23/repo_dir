#include<stdio.h>
#include<unistd.h>

int countlen(const char *s)
{
	int c,i;
	for(i=0;s[i];i++);
		return i;
}

char *my_strcat(char *d, const char*s)
{
	int c=countlen(d),i;
	for(i=0;s[i];i++)
	{
		d[c+i]=s[i];
	}
	d[c+countlen(s)]='\0';
	return d;
}

char *my_strncat(char *d, char *s , int c)
{
	int count=countlen(d),i;
	for(i=0;i<c;i++)
	{
		d[count+i]=s[i];
	}
	d[count+c]='\0';

}

void main()
{
	char s[30],d[50];
	printf("Enter the string...\n");
	scanf("%[^\n]",s);

	int c=countlen(s);
	printf("length is--> %d\n",c);
	
	my_strcat(d,s);
	printf("full string --> %s\n",d);
	
	printf("Enter char you want to concate-->\n");
	scanf(" %d",&c);
	my_strncat(d,s,c);
	printf("full string --> %s\n",d);
}
