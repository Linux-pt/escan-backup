#include<stdio.h>
#include<string>
#include<string.h>
#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sqlite3.h>
#include"zip.h"
#include"RestoreIncremental.h"
#include"On_Extract_Entry.h"
#include"Extract.h"
#include"HandleSigint.h"
using namespace std;
/*incremental backup if file sha1sum was not matched then*/
/*this function zip the file*/
/*On_Extract_Entry*/
extern sqlite3 *db;
/*
void RestoreIncremental(char *argv)
{
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	//WriteLogForlibmwshare(2,"RestoreIncremental started" );
	int count=0;
	//char tt[1024];
	char file_path[1024];
	sprintf(file_path,"/tmpdata/escanAV/escanIncremental/%s",argv);
	char dir_name[1024];
	//strcpy(file_path,argv);
	int arg = 2;
	zip_extract(file_path, "/tmpdata/escanAV/Restore/", On_Extract_Entry, &arg);
	//	char pp1[1024]="/tmpdata/escanAV/Restore/tmpdata";
	//WriteLogForlibmwshare(2,"RestoreIncremental ended" );
	return;
}
*/


/*incremental backup if file sha1sum was not matched then*/
/*this function zip the file*/
/*On_Extract_Entry*/
/*
void RestoreIncremental(char *argv)
{
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	//WriteLogForlibmwshare(2,"RestoreIncremental started" );
	int count=0;
	//char tt[1024];
	char file_path[1024];
	//sprintf(file_path,"/tmpdata/escanAV/escanIncremental/%s",argv);
	char dir_name[1024];
	//strcpy(file_path,argv);
	int arg = 2;
	zip_extract(argv, "/tmpdata/escanAV/Restore/", On_Extract_Entry, &arg);
	//	char pp1[1024]="/tmpdata/escanAV/Restore/tmpdata";
	//WriteLogForlibmwshare(2,"RestoreIncremental ended" );
	return;
}

*/


/*incremental backup if file sha1sum was not matched then*/
/*this function zip the file*/
/*On_Extract_Entry*/
/*
void RestoreIncremental(char *argv)

{
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	int count=0;
	char file_path[1024];
	char dir_name[1024];
	int arg = 2;
	
	zip_extract(argv, "/tmpdata/escanAV/Restore/", On_Extract_Entry, &arg);
	//	char pp1[1024]="/tmpdata/escanAV/Restore/tmpdata";
	//WriteLogForlibmwshare(2,"RestoreIncremental ended" );
	
	return;
}
*/


/*incremental backup if file sha1sum was not matched then*/
/*this function zip the file*/
/*On_Extract_Entry*/
void RestoreIncremental(char *argv)
{
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	int count=0;
	char file_path[1024];
	char dir_name[1024];
	int arg = 2;

	int vulnerable=0,Patched=0;
	


	if(ExtractZip((char *)argv,(char *)"/tmpdata/escanAV/Restore/" ,&vulnerable,&Patched)==-1)
	{
		printf("Failed to Extract Zip File \n");
		//return -1;
	}
	
	/*
	zip_extract(argv, "/tmpdata/escanAV/Restore/", On_Extract_Entry, &arg);
	//	char pp1[1024]="/tmpdata/escanAV/Restore/tmpdata";
	//WriteLogForlibmwshare(2,"RestoreIncremental ended" );
	*/
	return;
}



