#include "header.h"

void main()
{
	int a,b,op;
	printf("Enter the two number..\n");
	scanf("%d %d",&a,&b);
	while(1)
	{
		printf("Enter the opeion:-\n1-> addition\n2->subtraction\n3->multiplication\n4->addition\n ");
		scanf("%d",&op);
		switch(op)
		{
			case 1:add(a,b);
				break;
			case 2:sub(a,b);
				break;
			case 3:multi(a,b);
				break;
			case 4:divi(a,b);
				break;
			default: printf("un-known\n");
				 break;

		}
	}


}
