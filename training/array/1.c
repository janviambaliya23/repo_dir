#include<stdio.h>
#include<string.h>

void main()
{
	int a[5],ele,i;
	ele=sizeof(a)/sizeof(a[0]);
	printf("Enter the array element..\n");
	for(int i=0;i<ele;i++)
		scanf("%d",&a[i]);



	printf("\nYour araay ele..\n");
	for(i=0;i<ele;i++)
		printf("%d ",a[i]);
	printf("\n");
}
