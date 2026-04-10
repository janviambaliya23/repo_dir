#include<stdio.h>
#include<string.h>

void strong(int *a, int ele)
{
	int i,j,z,temp,sum,r,r1;
	for(i=0;i<ele;i++)
	{
		for(temp=a[i],sum=0,r=0;temp;temp/=10)
		{
			r=temp%10;
			for(z=1,r1=1;z<=r;z++)
				r1=z*r1;
			sum+=r1;
		}
		if(sum==a[i])
			printf("%d ",a[i]);
	}

}

void main()
{
	int a[5],ele,i;
	ele=sizeof(a)/sizeof(a[0]);
	printf("Enter the array element..\n");
	for(int i=0;i<ele;i++)
		scanf("%d",&a[i]);

	printf("you strong number is--> ");
	strong(a,ele);

	printf("\nYour araay ele..\n");
	for(i=0;i<ele;i++)
		printf("%d ",a[i]);
	printf("\n");
}
