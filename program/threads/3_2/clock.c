#include<stdio.h>
#include<time.h>

// man 2 time 

int main()
{

	time_t t;
	t=time(NULL);

	printf("second is-> %ld\n",t); // print in long int not undersatnd by human
/////////////////////////////////////////////////////////////////////

	printf("\n\ntime in string-->%s\n",ctime(&t)); // it print all data link month,date,day,time all in 1 function

/////////////////////////////////////////////////////////////////

struct tm *time_info= localtime(&t);

	printf("\n\n%d:%d:%d\n",time_info->tm_hour,time_info->tm_min,time_info->tm_sec); // print (hr, min, sec) formate huma readable

///////////////////////////////////////////////////////////////////

// time --> string

	char buffer[80];
	strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",time_info);
	printf("\n\nformate is-->%s\n",buffer);

////////////////////////////////////////////////////////////////////

//string  -> time

	printf("\n\nstring -> time\n");
	struct tm tm ={0};
	strptime("026-02-01 10:30:45","%Y-%m-%d %H:%M:%S",&tm);
	printf("year:- %d\n",tm.tm_year + 1900);
	printf("month:- %d\n",tm.tm_mon + 1);
	printf("day:- %d\n",tm.tm_mday);
	return 0;
}
