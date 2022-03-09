#include<string.h>
#include<stdio.h>
#include<string>
#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include"zip.h"
#include"WriteLogForlibmwshare.h"
#include<sqlite3.h>
#include"RestoreFolder.h"
#include"HandleSigint.h"
using namespace std;
/*this function will restore folder*/
/*using cp command*/
extern sqlite3 *db;
/*
void RestoreFolder(char *path)
{
	//printf("%s\n",path);
	signal(SIGINT, HandleSigint);


	char path10[1024]="";

	char actualpath8 [1024]="";
	char *ptrr8;

	ptrr8 = realpath(path, actualpath8);



	signal(SIGTERM, HandleSigint);
	//WriteLogForlibmwshare(2,"RestoreFolder started" );
	int count=0;
	char dir_name[1024];
	strcpy(dir_name,path);	
	char buff1[1024];
	//char buff2[1024];
	int inode_value;

	char new_path[1024]="";
	sqlite3_stmt *res1;
	if(sqlite3_prepare_v2(db,"SELECT * FROM PATH WHERE PATH=?;",-1,&res1,NULL))
	{
		WriteLogForlibmwshare(4,"Error in RestoreFolder in sqlite3_prepare_v2 while selecting the data from path table" );
		printf("error in prepare v2=%d\n",__LINE__);
		sqlite3_close(db);
		exit(-1);
	}

	sqlite3_bind_text(res1,1,ptrr8,-1,NULL);

	if(sqlite3_step(res1)!=SQLITE_OK)
	{
		checking that full backup are already present or not
		if not then return NULL else it will continue
		if(sqlite3_column_type(res1, 0) == SQLITE_NULL)
		{
			WriteLogForlibmwshare(4,"RestoreFolder the folder was not present" );
		}
		else
		{
			//	printf("%s\n%s\n",inode_value,new_path);
			strcpy(new_path,(const char *)sqlite3_column_text(res1,1));									
			inode_value=sqlite3_column_int(res1,2);								
		}
	}
	sprintf(buff1,"cp -rf /tmpdata/escanAV/Backup/%d /tmpdata/escanAV/Restore/'%d' ",inode_value,inode_value);

	system(buff1);
	//WriteLogForlibmwshare(2,"RestoreFolder ended" );


}

*/
/*this function will restore folder*/
/*using cp command*/
/*
void RestoreFolder(char *path)
{
	//printf("%s\n",path);
	signal(SIGINT, HandleSigint);


	char path10[1024]="";

	char actualpath8 [1024]="";
	char *ptrr8;

	ptrr8 = realpath(path, actualpath8);



	signal(SIGTERM, HandleSigint);
	//WriteLogForlibmwshare(2,"RestoreFolder started" );
	int count=0;
	char dir_name[1024];
	strcpy(dir_name,path);	
	char buff1[1024];
	//char buff2[1024];
	int inode_value=0;
	char encode_path[1024]="";

	char new_path[1024]="";
	sqlite3_stmt *res1;
	if(sqlite3_prepare_v2(db,"SELECT * FROM PATH WHERE PATH=?;",-1,&res1,NULL))
	{
		WriteLogForlibmwshare(4,"Error in RestoreFolder in sqlite3_prepare_v2 while selecting the data from path table" );
		printf("error in prepare v2=%d\n",__LINE__);
		sqlite3_close(db);
		exit(-1);
	}

	sqlite3_bind_text(res1,1,ptrr8,-1,NULL);
	if(sqlite3_step(res1)!=SQLITE_OK)
	{
		checking that full backup are already present or not
		if not then return NULL else it will continue
		if(sqlite3_column_type(res1, 0) == SQLITE_NULL)
		{
			WriteLogForlibmwshare(4,"RestoreFolder the folder was not present" );
		}
		else
		{
			strcpy(new_path,(const char *)sqlite3_column_text(res1,1));									
			strcpy(encode_path,(const char *)sqlite3_column_text(res1,2));	
	//		strcpy(encode_path,encoded_path(new_path).c_str());
		//	printf("encoded_path=%s\n",encode_path);			
		//	printf("path=%s\n",path);			
		//	inode_value=sqlite3_column_int(res1,2);								
		}
		//sprintf(buff1,"cp -rf /tmpdata/escanAV/Backup/'%s' /tmpdata/escanAV/Restore/'%s' ",encoded_path,path);
		sprintf(buff1,"cp -rf /tmpdata/escanAV/Backup/'%s' /tmpdata/escanAV/Restore/'%s' ",encode_path,encode_path);

		system(buff1);

	}
	//WriteLogForlibmwshare(2,"RestoreFolder ended" );


}


*/


/*this function will restore folder*/
/*using cp command*/
void RestoreFolder(char *path)
{
	//printf("%s\n",path);
	signal(SIGINT, HandleSigint);


	char path10[1024]="";

	char actualpath8 [1024]="";
	char *ptrr8;

	ptrr8 = realpath(path, actualpath8);



	signal(SIGTERM, HandleSigint);
	//WriteLogForlibmwshare(2,"RestoreFolder started" );
	int count=0;
	char dir_name[1024];
	strcpy(dir_name,path);	
	char buff1[1024];
	//char buff2[1024];
	int inode_value=0;
	char encode_path[1024]="";

	char new_path[1024]="";
	sqlite3_stmt *res1;
	if(sqlite3_prepare_v2(db,"SELECT * FROM PATH WHERE PATH=?;",-1,&res1,NULL))
	{
		WriteLogForlibmwshare(4,"Error in RestoreFolder in sqlite3_prepare_v2 while selecting the data from path table" );
		printf("error in prepare v2=%d\n",__LINE__);
		sqlite3_close(db);
		exit(-1);
	}

	sqlite3_bind_text(res1,1,ptrr8,-1,NULL);
	/**/
	if(sqlite3_step(res1)!=SQLITE_OK)
	{
		/*checking that full backup are already present or not*/
		/*if not then return NULL else it will continue*/
		if(sqlite3_column_type(res1, 0) == SQLITE_NULL)
		{
			WriteLogForlibmwshare(4,"RestoreFolder the folder was not present" );
		}
		else
		{
			strcpy(new_path,(const char *)sqlite3_column_text(res1,1));									
			strcpy(encode_path,(const char *)sqlite3_column_text(res1,2));	
	//		strcpy(encode_path,encoded_path(new_path).c_str());
		//	printf("encoded_path=%s\n",encode_path);			
		//	printf("path=%s\n",path);			
		//	inode_value=sqlite3_column_int(res1,2);								
		}
		//sprintf(buff1,"cp -rf /tmpdata/escanAV/Backup/'%s' /tmpdata/escanAV/Restore/'%s' ",encoded_path,path);
		sprintf(buff1,"cp -rf /tmpdata/escanAV/Backup/'%s' /tmpdata/escanAV/Restore/'%s' ",encode_path,encode_path);

		system(buff1);

	}
	//WriteLogForlibmwshare(2,"RestoreFolder ended" );


}




