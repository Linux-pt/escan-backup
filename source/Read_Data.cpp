#include<stdio.h>
#include<string.h>
#include<string>
#include<iostream>
#include<signal.h>
#include"HandleSigint.h"
#include"WriteLogForlibmwshare.h"
#include<stdlib.h>
#include<sqlite3.h>
#include<unistd.h>
#include"Read_Data.h"
using namespace std;

/*this will print the data from databse table*/
extern sqlite3 *db;
extern int flag;
void PrintColumnValue(sqlite3_stmt* stmt, int col) 
{
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);

	//WriteLogForlibmwshare(2,"PrintColumnValue started" );
	int colType = sqlite3_column_type(stmt, col);

	switch(colType) 
	{

		case SQLITE_INTEGER:
			printf("%d\n", sqlite3_column_int(stmt, col));
			break;

		case SQLITE_FLOAT:
			printf("%f\n", sqlite3_column_double(stmt, col));
			break;

		case SQLITE_TEXT:
			printf("%s\n", sqlite3_column_text(stmt, col));
			break;

		case SQLITE_NULL:
			printf("null\n");
			break;

		case SQLITE_BLOB:
			printf("blob\n");
			break;
	}
	//WriteLogForlibmwshare(2,"PrintColumnValue ended" );

}





/*read data from tmpdata table*/
/*PrintColumnValue*/
void Read_Tmpdata()
{
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	//WriteLogForlibmwshare(2,"Read_Tmpdata started" );
	sqlite3_stmt *stmt;
	if(sqlite3_prepare_v2(db,"SELECT * FROM TMPDATA;",-1,&stmt,NULL))
	{
		WriteLogForlibmwshare(2,"Error in Read_Tmpdata" );
		//printf("error in exec query\n");
		sqlite3_close(db);
		exit(-1);
	}
	while(sqlite3_step(stmt)!=SQLITE_DONE && !flag)
	{
		for(int i=0;i<4;i++)
		{
			PrintColumnValue(stmt,i);

		}


	}
	//WriteLogForlibmwshare(2," Read_Tmpdata ended" );
	//	sqlite3_reset(stmt);
}

/*reading backup data*/
/*PrintColumnValue*/
void Read_BackupData()
{
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	//WriteLogForlibmwshare(2,"Read_BackupData  started" );
	sqlite3_stmt *stmt;
	if(sqlite3_prepare_v2(db,"SELECT * FROM BACKUP;",-1,&stmt,NULL))
	{
		WriteLogForlibmwshare(2,"Error in Read_BackupData" );
		//printf("error in exec query\n");
		sqlite3_close(db);
		exit(-1);
	}
	while(sqlite3_step(stmt)!=SQLITE_DONE && !flag)
	{
		for(int i=0;i<4;i++)
		{
			PrintColumnValue(stmt,i);

		}



	}
	//WriteLogForlibmwshare(2," Read_BackupData ended" );
	//	sqlite3_reset(stmt);
}


