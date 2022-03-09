#include<stdio.h>
#include<string.h>
#include<string>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sqlite3.h>
#include<iostream>
#include"remove_folder.h"
#include"WriteLogForlibmwshare.h"
#include"HandleSigint.h"
#include<pthread.h>
using namespace std;
extern sqlite3 *db;

static int remove_folder(const char *pathname, const struct stat *sbuf, int type, struct FTW *ftwb)
{
	//WriteLogForlibmwshare(2,"remove_folder started" );
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	if(remove(pathname) < 0)
	{
		WriteLogForlibmwshare(2,"Error in remove_folder function " );
		perror("ERROR: remove");
		return -1;
	}
	//WriteLogForlibmwshare(2,"remove_folder ended" );
	return 0;
}



