#include<stdio.h>
#include<string.h>
#include<iostream>
#include<string>
#include<stdlib.h>
#include<unistd.h>
#include<sqlite3.h>
#include<signal.h>
#include"On_Extract_Entry.h"
#include"WriteLogForlibmwshare.h"
#include"HandleSigint.h"
#include"Extract.h"
using namespace std;
/*incremental backup if file sha1sum was not matched then*/
/*this function zip the file*/
/*On_Extract_Entry*/
extern sqlite3 *db;
/*
void RestoreIncremental_For_BeforeAfter(char *argv)
{
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	//WriteLogForlibmwshare(2,"RestoreIncremental started" );
	int count=0;
	//char tt[1024];

	char file_path[1024]="";
	char new_path[1024]="";
	sprintf(file_path,"/tmpdata/escanAV/escanIncremental/%s",argv);
	//printf("%s\n",file_path);
	
	//printf("restore folder was started\n");

	sqlite3_stmt *res1;
	if(sqlite3_prepare_v2(db,"SELECT NAME FROM INCREMENTAL WHERE TIME=(SELECT MAX(TIME) FROM INCREMENTAL WHERE PATH=(SELECT PATH FROM INCREMENTAL WHERE NAME=?));",-1,&res1,NULL))
	{
		WriteLogForlibmwshare(4,"Error in RestoreFolder in sqlite3_prepare_v2 while selecting the data from path table" );
		printf("error in prepare v2=%d\n",__LINE__);
		sqlite3_close(db);
		exit(-1);
	}

	sqlite3_bind_text(res1,1,file_path,-1,NULL);
	
	//if(sqlite3_step(res1)!=SQLITE_OK)
	if(sqlite3_step(res1)!=SQLITE_OK)
	{
		//printf("sqlite3_step was stareted\n");
		//printf("%s\n",sqlite3_column_text(res1,0));

		//if(sqlite3_column_type(res1, 0) == SQLITE_NULL)
		if(sqlite3_column_type(res1, 0) == SQLITE_NULL)
		{
			//printf("sqlite3_column_type was null\n");
		//	WriteLogForlibmwshare(4,"RestoreFolder the folder was not present" );
		}
		else
		{
			//printf("zipping was stareted\n");
			strcpy(new_path,(const char *)sqlite3_column_text(res1,0));								
			//printf("new_path=%s\n",new_path);

				int arg = 2;
			//zip_extract(file_path, "/tmpdata/escanAV/Restore/", On_Extract_Entry, &arg);
		//	zip_extract(new_path, "/tmpdata/escanAV/Restore/", On_Extract_Entry, &arg);
		
		}

	}



	char dir_name[1024];
	//strcpy(file_path,argv);
	//printf("%s\n",file_path);
//	int arg = 2;
//	zip_extract(file_path, "/tmpdata/escanAV/Restore/", On_Extract_Entry, &arg);
	//	char pp1[1024]="/tmpdata/escanAV/Restore/tmpdata";
	//WriteLogForlibmwshare(2,"RestoreIncremental ended" );
	return;
}

*/

/*incremental backup if file sha1sum was not matched then*/
/*this function zip the file*/
/*On_Extract_Entry*/
void RestoreIncremental_For_BeforeAfter(char *argv)
{
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	//WriteLogForlibmwshare(2,"RestoreIncremental started" );
	int count=0;
	//char tt[1024];

	char file_path[1024]="";
	char new_path[1024]="";
	sprintf(file_path,"/tmpdata/escanAV/escanIncremental/%s",argv);
	//printf("%s\n",file_path);
	
	//printf("restore folder was started\n");

	sqlite3_stmt *res1;
	if(sqlite3_prepare_v2(db,"SELECT NAME FROM INCREMENTAL WHERE TIME=(SELECT MAX(TIME) FROM INCREMENTAL WHERE PATH=(SELECT PATH FROM INCREMENTAL WHERE NAME=?));",-1,&res1,NULL))
	{
		WriteLogForlibmwshare(4,"Error in RestoreFolder in sqlite3_prepare_v2 while selecting the data from path table" );
		printf("error in prepare v2=%d\n",__LINE__);
		sqlite3_close(db);
		exit(-1);
	}

	sqlite3_bind_text(res1,1,file_path,-1,NULL);
	
	//if(sqlite3_step(res1)!=SQLITE_OK)
	if(sqlite3_step(res1)!=SQLITE_OK)
	{
		//printf("sqlite3_step was stareted\n");
		//printf("%s\n",sqlite3_column_text(res1,0));

		//if(sqlite3_column_type(res1, 0) == SQLITE_NULL)
		if(sqlite3_column_type(res1, 0) == SQLITE_NULL)
		{
			//printf("sqlite3_column_type was null\n");
		//	WriteLogForlibmwshare(4,"RestoreFolder the folder was not present" );
		}
		else
		{
			//printf("zipping was stareted\n");
			strcpy(new_path,(const char *)sqlite3_column_text(res1,0));								
			//printf("new_path=%s\n",new_path);
			int vulnerable=0,Patched=0;



			if(ExtractZip((char *)file_path,(char *)"/tmpdata/escanAV/Restore/" ,&vulnerable,&Patched)==-1)
			{
				printf("Failed to Extract Zip File \n");
				//return -1;
			}

				int arg = 2;
			//zip_extract(file_path, "/tmpdata/escanAV/Restore/", On_Extract_Entry, &arg);
			//zip_extract(new_path, "/tmpdata/escanAV/Restore/", On_Extract_Entry, &arg);
		
		}

	}



	char dir_name[1024];
	//strcpy(file_path,argv);
	//printf("%s\n",file_path);
//	int arg = 2;
//	zip_extract(file_path, "/tmpdata/escanAV/Restore/", On_Extract_Entry, &arg);
	//	char pp1[1024]="/tmpdata/escanAV/Restore/tmpdata";
	//WriteLogForlibmwshare(2,"RestoreIncremental ended" );
	return;
}



