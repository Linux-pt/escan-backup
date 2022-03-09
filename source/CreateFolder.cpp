#include<stdio.h>
#include<signal.h>
#include<fstream>
#include<iostream>
#include <sys/stat.h>
#include"HandleSigint.h"
#include<sqlite3.h>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include"CreateFolder.h"
using namespace std;

/*if file structure was not present then we create*/
/*this file structure like*/
/*/tmpdata/escanAV/(backup/escanincremental/Restore/databse(.backup))*/
extern sqlite3 *db;
int CreateFolder()
{
	signal(SIGINT, HandleSigint);
	//WriteLogForlibmwshare(2,"CreateFolder started" );
	int status;
	status = mkdir("/tmpdata/", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	if(status == 0)
	{
		//	WriteLogForlibmwshare(2,"tmpdata directory is created" );		
	}
	else
	{
		//WriteLogForlibmwshare(2,"tmpdata directory is already created" );				
	}
	status = mkdir("/tmpdata/escanAV", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	if(status == 0)
	{
		//	WriteLogForlibmwshare(2,"tmpdata/escanAV directory was cerated" );		
	}
	else
	{

		//WriteLogForlibmwshare(2,"tmpdata/escanAV was already present" );		
	}

	status = mkdir("/tmpdata/escanAV/Backup", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	if(status == 0)
	{
		//	WriteLogForlibmwshare(2,"tmpdata/escanAV/Backup directory was created" );		
	}
	else
	{

		//	WriteLogForlibmwshare(2,"tmpdata/escanAV/Backup directory was already present" );		
	}

	status = mkdir("/tmpdata/escanAV/escanIncremental", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	if(status == 0)
	{
		//	WriteLogForlibmwshare(2,"tmpdata/escanAV/escanIncremental directory was cerated" );		
	}
	else
	{
		//	WriteLogForlibmwshare(2,"tmpdata/escanAV/escanIncremental directory was already present" );		
	}

	status = mkdir("/tmpdata/escanAV/Restore", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	if(status == 0)
	{
		//	WriteLogForlibmwshare(2,"tmpdata/escanAV/Restore directory was created" );		
	}
	else
	{
		//WriteLogForlibmwshare(2,"tmpdata/escanAV/Restore directory was already present" );		

	}

	//WriteLogForlibmwshare(2,"CreateFolder ended" );
	return 0;
}



