#include<stdio.h>
#include<iostream>
#include<string>
#include<string.h>
#include"As_Per_Time_Filename.h"
#include<stdlib.h>
#include<signal.h>
#include<sqlite3.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<time.h>
#include<unistd.h>
#include<sys/time.h>
#include"HandleSigint.h"
using namespace std;
/*it is used to create the filename as per filename and timestamp*/
/*we are creating filename here as per requirement*/
extern sqlite3 *db;
/*
string As_Per_Time_Filename()
{
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);

	//WriteLogForlibmwshare(2,"As_Per_Time_Filename started" );
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[1024];

	time (&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer,sizeof(buffer),"%d-%m-%Y_%H:%M:%S",timeinfo);

	struct timeval te;
	gettimeofday(&te, NULL); // get current time
	long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
	char buff1[1024];
	sprintf(buff1,"%s_%lld",buffer,milliseconds);
	string str(buff1);
	//WriteLogForlibmwshare(2,"As_Per_Time_Filename ended" );
	return str;

}
*/

int As_Per_Time_Filename(char *name,long long int *epoch)
{
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);

	//WriteLogForlibmwshare(2,"As_Per_Time_Filename started" );
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[1024];

	time (&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer,sizeof(buffer),"%d-%m-%Y_%H:%M:%S",timeinfo);

	struct timeval te;
	gettimeofday(&te, NULL); // get current time
	long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
	char buff1[1024];
	sprintf(buff1,"%s_%lld",buffer,milliseconds);
	//string str(buff1);
	strcpy(name,buff1);
	//strcpy(epoch,(char *)milliseconds);
	*epoch=milliseconds;

	printf("%s\n",name);
	printf("%lld\n",*epoch);
	//WriteLogForlibmwshare(2,"As_Per_Time_Filename ended" );
	//return str;
	return 0;
}


