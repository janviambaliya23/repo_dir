#include<stdio.h>
#include<stdlib.h>

int count_len(const char *s)
{
          int c=0;
          for(int i=0;s[i];i++)
                  c++;
          return c;                  
}
char *my_strcat(char *dest, const char *src)
{
              int i;
              char *p=malloc(sizeof(char) * 30);
              int c=count_len(dest);
             printf("len of des--> %d\n",c);
	    for(i=0;dest[i];i++)
	    {
	    	p[i]=dest[i];
	    } 
	    int j=0;
	     for( ;src[j];j++,i++)
             {
                      p[i]=src[j];
            }
            p[i]='\0';
           
	    return p;
}

void main()
{
	char s[30],d[30];
	printf("Enter soucr string..\n");
	scanf(" %[^\n]",s);
	printf("Enter desti string..\n");
	scanf(" %[^\n]",d);
	char *p=my_strcat(d,s);
	printf("sting is--> %s\n",p);
	free(p);
}
