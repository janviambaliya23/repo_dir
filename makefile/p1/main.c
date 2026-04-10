#include "header.h"

int main()
{
	int a,b;
	printf("Enter 1st number..\n");
	scanf("%d",&a);
	printf("Enter 2st number..\n");
	scanf("%d",&b);

//	printf("PI-> %f\n",PI);
	printf("addition=> %d\n",sum(a,b));
	printf("subtraction=> %d\n",sub(a,b));
	printf("multiplication=> %d\n",mul(a,b));
	printf("division=> %f\n",divi(a,b));
	return 0;
}
