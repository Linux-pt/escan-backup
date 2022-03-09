#include<stdio.h>
#include<string>
#include<string.h>
#include<iostream>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sqlite3.h>
#include<signal.h>
#include"HandleSigint.h"
#include"fileRemove.h"
using namespace std;
/*this function will remove files after year*/
extern sqlite3 *db;
void fileRemove(char *unzip)
{
	//WriteLogForlibmwshare(2,"fileRemove started" );
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	char file_name_remove[1024]="";
	sprintf(file_name_remove,"/tmpdata/escanAV/escanIncremental/%s",unzip);
	remove(file_name_remove);
	//WriteLogForlibmwshare(2,"fileRemove ended" );

}



