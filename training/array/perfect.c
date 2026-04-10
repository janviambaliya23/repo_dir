#include<stdio.h>
#include<string.h>

void perfect(int *a, int ele)
{
	int i,j,sum,temp;
	for(i=0;i<ele;i++)
	{
		for(sum=0,temp=a[i],j=1;j<temp;j++)
		{
			if(temp%j==0)
			{
				sum+=j;
			}
		}
		if(sum==a[i])
			printf("%d ",sum);
	}
}

void main()
{
	int a[5],ele,i;
	ele=sizeof(a)/sizeof(a[0]);
	printf("Enter the array element..\n");
	for(int i=0;i<ele;i++)
		scanf("%d",&a[i]);

	printf("perfect number--> ");
	perfect(a,ele);


	printf("\nYour araay ele..\n");
	for(i=0;i<ele;i++)
		printf("%d ",a[i]);
	printf("\n");
}
