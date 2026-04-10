#include<stdio.h>
#include<string.h>

void prime(int *a,int ele)
{
	int i,j;
	for(i=0;i<ele;i++)
	{
		for(j=2;j<a[i];j++)
		{
			if(a[i]%j==0)
				break;
		}
		if(a[i]==j)
		{
			printf("%d ",a[i]);
		}
	}
}


void main()
{
	int a[5],ele,i;
	ele=sizeof(a)/sizeof(a[0]);
	printf("Enter the array element..\n");
	for(int i=0;i<ele;i++)
		scanf("%d",&a[i]);

	printf("prime number is-> ");
	prime(a,ele);
	
	printf("\nYour araay ele..\n");
	for(i=0;i<ele;i++)
		printf("%d ",a[i]);
	printf("\n");
}
