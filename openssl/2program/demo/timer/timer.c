#include "header.h"

void main()
{
	srand(getpid());
	time_t cur_time,delay_time;
	struct tm *time_get;
	char buff[20];
//////////////////////////////////////////////

	for(int i=0;i<5;i++)
	{
		time(&cur_time);
		printf("current time-> %ld\n",cur_time);
		//-------------------	
		time_get=localtime(&cur_time);
		strftime(buff,sizeof(buff),"%H:%M:%S",time_get);
		printf("old time--> %s\n",buff);


//------------------------- rand	
		int n=rand()%10+1;
		printf("sencond is--> %d\n",n);
		sleep(n);

//--------------------------  again take value
		time(&delay_time);
		printf("\ndelay time-> %ld\n",delay_time);
		//-------------------
		time_get=localtime(&delay_time);
		strftime(buff,sizeof(buff),"%H:%M:%S",time_get);
                printf("old time--> %s\n",buff);


//---------------------------   diffrence
		double diff_time=difftime(delay_time,cur_time);
		printf("diffence is-> %f\n",diff_time);

		if(diff_time<=5)
		{
			printf("less than 5 sec...\n\n\n");
		}
		else
			printf("more than 5 sec...\n\n\n");

		printf("------------------------------------------\n");
	}
}
