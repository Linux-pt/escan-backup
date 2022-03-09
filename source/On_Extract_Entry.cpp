#include<stdio.h>
#include<string.h>
#include<string>
#include<stdlib.h>
#include"On_Extract_Entry.h"
#include<sqlite3.h>
#include"HandleSigint.h"
#include<signal.h>
using namespace std;

/*it is used to create extract entry from zip file*/
/*libzip.so are mandatory for this please search for this*/
extern sqlite3 *db;
/*
int On_Extract_Entry(const char *filename, void *arg) 
{
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	//WriteLogForlibmwshare(2,"On_Extract_Entry started" );
	static int i = 0;
	int n = *(int *)arg;
	//	printf("Extracted: %s (%d of %d)\n", filename, ++i, n);

	//WriteLogForlibmwshare(2,"On_Extract_Entry ended" );
	return 0;
}

*/

/*it is used to create extract entry from zip file*/
/*libzip.so are mandatory for this please search for this*/
int On_Extract_Entry(const char *filename, void *arg) 
{
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	//WriteLogForlibmwshare(2,"On_Extract_Entry started" );
	static int i = 0;
	int n = *(int *)arg;
	//	printf("Extracted: %s (%d of %d)\n", filename, ++i, n);

	//WriteLogForlibmwshare(2,"On_Extract_Entry ended" );
	return 0;
}



