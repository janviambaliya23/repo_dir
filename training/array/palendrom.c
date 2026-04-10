#include<stdio.h>
#include<string.h>

void paladrom(int *a,int ele)
{
	int i,j,temp=0,real=0,r=0;
	for(i=0;i<ele;i++)
	{
		for(temp=a[i],r=0,real=0;temp;temp/=10)
		{
			r=temp%10;
			real=real*10+r;
		}
		if(real==a[i])
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

	printf("palandrom is--> ");
	paladrom(a,ele);


	printf("\nYour araay ele..\n");
	for(i=0;i<ele;i++)
		printf("%d ",a[i]);
	printf("\n");
}
