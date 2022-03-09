#include<stdio.h>
#include<string>
#include<string.h>
#include<iostream>
#include<stdlib.h>
#include<iostream>
#include<unistd.h>
#include<sqlite3.h>
#include"HandleSigint.h"
#include<signal.h>
       #include <sys/stat.h>
#include"encoded_path.h"
using namespace std;

/*for copying data in full backup*/
/*HandleSigint*/
extern sqlite3 *db;
/*for copying data in full backup*/
/*
void CopyFiles_fullbackup(char *path)
{
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	//WriteLogForlibmwshare(2,"CopyFiles started" );
	char buff[1024];
//	struct stat stats;
//	stat(path,&stats);
	char new_path[1024]="";
	strcpy(new_path,encoded_path(path).c_str());
	sprintf(buff,"cp -rf %s /tmpdata/escanAV/Backup/'%s' ",path,new_path);
	system(buff);
	//WriteLogForlibmwshare(2,"CopyFiles ended" );

}

*/

/*for copying data in full backup*/
void CopyFiles_fullbackup(char *path)
{
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	//WriteLogForlibmwshare(2,"CopyFiles started" );
	char buff[1024];
//	struct stat stats;
//	stat(path,&stats);
	char new_path[1024]="";
	strcpy(new_path,encoded_path(path).c_str());
	sprintf(buff,"cp -rf %s /tmpdata/escanAV/Backup/'%s' ",path,new_path);
	system(buff);
	//WriteLogForlibmwshare(2,"CopyFiles ended" );

}



