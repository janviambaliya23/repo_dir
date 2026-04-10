#include<stdio.h>
#include<string.h>

void arm_strong(int *a,int ele)
{
	int i,j,temp,sum,c,r1,r,z;
	for(i=0;i<ele;i++)
	{
		for(c=0,j=a[i];j;j/=10,c++);
		for(temp=a[i],sum=0,r=0;temp;temp/=10)
		{
			r=temp%10;
			for(r1=1,z=0;z<c;z++)
			{
				r1=r1*r;
			}
			sum+=r1;
		}
		if(sum==a[i])
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


	printf("armstronf number is---> ");
	arm_strong(a,ele);
	
	printf("\nYour araay ele..\n");
	for(i=0;i<ele;i++)
		printf("%d ",a[i]);
	printf("\n");
}
