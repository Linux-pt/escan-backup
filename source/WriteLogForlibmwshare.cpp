#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<unistd.h>
#include<string>
#include<signal.h>
#include"HandleSigint.h"
#include"WriteLogForlibmwshare.h"
using namespace std;
void WriteLogForlibmwshare(short int reqDebugLevel, string logLine )
{
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	char confLogValue[25]="2";
	/*	if(readConfiguration("/opt/MicroWorld/etc/commonsettings.conf", "Config:DebugLevel", confLogValue) != 0)
		{
		readConfiguration("/opt/MicroWorld/etc/updates.conf", "Update:LogLevel", confLogValue);
		}
		*/	
	time_t sinceepoch = time(NULL); 
	struct tm *rpt_time = localtime(&sinceepoch); 
	char rtime[24]; 
	memset(rtime, 0, 24); 
	strftime(rtime, 23, "[%d-%b-%Y@%H:%M:%S] ", rpt_time);

	if(reqDebugLevel <= atoi(confLogValue) )
	{
		FILE *fp = fopen("/var/MicroWorld/var/log/ebackup.log", "a");
		if(fp == NULL)
		{
			system("mkdir -p /var/MicroWorld/var/log/");
			FILE *fp = fopen("/var/MicroWorld/var/log/ebackup.log", "a");
			if(fp == NULL)
			{
				return;
			}
		}
		fprintf(fp,"%s ", rtime );
		fprintf(fp, "%s\n",logLine.c_str() ? logLine.c_str() :"NULL");
		fclose(fp);
	}
}


