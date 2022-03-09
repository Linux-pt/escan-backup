#include<stdio.h>
#include<string.h>
#include<string>
#include<iostream>
#include<sqlite3.h>
#include<unistd.h>
#include<signal.h>
#include"HandleSigint.h"
using namespace std;
/*handle the signal*/
extern sqlite3 *db;
extern int flag;
void HandleSigint(int sig)
{
	//WriteLogForlibmwshare(2,"HandleSigint started" );

	flag=1;
	/*	if(sig==2)
		{
		sleep(2);
		return;
		}
		if(sig==15)
		{
		sleep(2);
		return;
		}
		*/	//WriteLogForlibmwshare(2,"HandleSigint ended" );
}


