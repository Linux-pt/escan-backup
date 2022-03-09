#include<stdio.h>
#include<sqlite3.h>
#include<string>
#include<string.h>
#include<signal.h>
#include<stdlib.h>
#include<iostream>
#include<unistd.h>
#include"DatabaseOpen.h"
#include"HandleSigint.h"
#include"WriteLogForlibmwshare.h"
using namespace std;
extern sqlite3 *db;
/*
int DatabaseOpen()
{
	checking whether backup present or not if not then return -1
	else return something else
	signal(SIGTERM, HandleSigint);
	signal(SIGINT, HandleSigint);
	int fd=access("/tmpdata/escanAV/.backup.db",F_OK);

	if(fd==-1)
	{

		if(sqlite3_open("/tmpdata/escanAV/.backup.db",&db))
		{
			WriteLogForlibmwshare(2,"Error in DatabaseOpen function in opening database" );
			//printf("error in oening backup.db:%d\n",__LINE__);
			sqlite3_close(db);
			exit(-1);
		}
		//if(sqlite3_exec(db,"CREATE TABLE BACKUP(ID INTEGER PRIMARY KEY AUTOINCREMENT,NAME TEXT,PATH TEXT,SHA1SUM TEXT);"
		int i1=(sqlite3_exec(db,"CREATE TABLE BACKUP(ID INTEGER PRIMARY KEY AUTOINCREMENT,NAME TEXT,PATH TEXT,SHA1SUM TEXT);",NULL,NULL,NULL));
		if(i1!=0)
		{
			WriteLogForlibmwshare(2,"Error in DatabaseOpen in sqlite3_exec in creating backup table" );
			//printf("ERROR CREATING BAACKUP TABLE:%d\n",__LINE__);
			sqlite3_close(db);
			exit(-1);
		}
		else
		{
			int ii1=(sqlite3_exec(db,"CREATE TABLE BACKUP(ID INTEGER PRIMARY KEY AUTOINCREMENT,NAME TEXT,PATH TEXT,SHA1SUM TEXT);",NULL,NULL,NULL));
		}
		int i2=(sqlite3_exec(db,"CREATE TABLE TMPDATA(ID INTEGER PRIMARY KEY AUTOINCREMENT,NAME TEXT,PATH TEXT,SHA1SUM TEXT);",NULL,NULL,NULL));
		if(i2!=0)
		{
			WriteLogForlibmwshare(2,"Error in DatabaseOpen in creating tmpdata table in sqlite3_exec" );
			//printf("ERROR CREATING TMPDATA TABLE:%d\n",__LINE__);
			sqlite3_close(db);
			exit(-1);
		}
		else
		{
			int ii2=(sqlite3_exec(db,"CREATE TABLE TMPDATA(ID INTEGER PRIMARY KEY AUTOINCREMENT,NAME TEXT,PATH TEXT,SHA1SUM TEXT);",NULL,NULL,NULL));
		}

		int i3=(sqlite3_exec(db,"CREATE TABLE PATH(ID INTEGER PRIMARY KEY AUTOINCREMENT, PATH TEXT,INODE INTEGER);",NULL,NULL,NULL));
		if(i3!=0)
		{
			WriteLogForlibmwshare(2,"Error in DatabaseOpen in sqlite3_exec in creating table path" );
			//printf("ERROR CREATING PATH TABLE:%d\n",__LINE__);
			sqlite3_close(db);
			exit(-1);
		}
		else
		{
			int ii3=(sqlite3_exec(db,"CREATE TABLE PATH(ID INTEGER PRIMARY KEY AUTOINCREMENT, PATH TEXT,INODE INTEGER);",NULL,NULL,NULL));
		}



		//	WriteLogForlibmwshare(4,"All table created successfully" );
	}


	else
	{
		if(sqlite3_open("/tmpdata/escanAV/.backup.db",&db))
		{
			WriteLogForlibmwshare(2,"Error in DatabaseOpen in sqlite3_open in opening database" );
			//printf("error in oening backup.db:%d\n",__LINE__);
			sqlite3_close(db);
			exit(-1);
		}
	}	

	return 0;	
}
*/

int DatabaseOpen()
{
	/*checking whether backup present or not if not then return -1*/
	/*else return something else*/
	signal(SIGTERM, HandleSigint);
	signal(SIGINT, HandleSigint);
	int fd=access("/tmpdata/escanAV/.backup.db",F_OK);

	if(fd==-1)
	{

		if(sqlite3_open("/tmpdata/escanAV/.backup.db",&db))
		{
			WriteLogForlibmwshare(2,"Error in DatabaseOpen function in opening database" );
			//printf("error in oening backup.db:%d\n",__LINE__);
			sqlite3_close(db);
			exit(-1);
		}
		//if(sqlite3_exec(db,"CREATE TABLE BACKUP(ID INTEGER PRIMARY KEY AUTOINCREMENT,NAME TEXT,PATH TEXT,SHA1SUM TEXT);"
		int i1=(sqlite3_exec(db,"CREATE TABLE BACKUP(ID INTEGER PRIMARY KEY AUTOINCREMENT,NAME TEXT,PATH TEXT,SHA1SUM TEXT);",NULL,NULL,NULL));
		if(i1!=0)
		{
			WriteLogForlibmwshare(2,"Error in DatabaseOpen in sqlite3_exec in creating backup table" );
			//printf("ERROR CREATING BAACKUP TABLE:%d\n",__LINE__);
			sqlite3_close(db);
			exit(-1);
		}
		else
		{
			int ii1=(sqlite3_exec(db,"CREATE TABLE BACKUP(ID INTEGER PRIMARY KEY AUTOINCREMENT,NAME TEXT,PATH TEXT,SHA1SUM TEXT);",NULL,NULL,NULL));
		}
		int i2=(sqlite3_exec(db,"CREATE TABLE TMPDATA(ID INTEGER PRIMARY KEY AUTOINCREMENT,NAME TEXT,PATH TEXT,SHA1SUM TEXT);",NULL,NULL,NULL));
		if(i2!=0)
		{
			WriteLogForlibmwshare(2,"Error in DatabaseOpen in creating tmpdata table in sqlite3_exec" );
			//printf("ERROR CREATING TMPDATA TABLE:%d\n",__LINE__);
			sqlite3_close(db);
			exit(-1);
		}
		else
		{
			int ii2=(sqlite3_exec(db,"CREATE TABLE TMPDATA(ID INTEGER PRIMARY KEY AUTOINCREMENT,NAME TEXT,PATH TEXT,SHA1SUM TEXT);",NULL,NULL,NULL));
		}

		int i3=(sqlite3_exec(db,"CREATE TABLE PATH(ID INTEGER PRIMARY KEY AUTOINCREMENT, PATH TEXT,PATH_ENCODED TEXT);",NULL,NULL,NULL));
		if(i3!=0)
		{
			WriteLogForlibmwshare(2,"Error in DatabaseOpen in sqlite3_exec in creating table path" );
			//printf("ERROR CREATING PATH TABLE:%d\n",__LINE__);
			sqlite3_close(db);
			exit(-1);
		}
		else
		{
			int ii3=(sqlite3_exec(db,"CREATE TABLE PATH(ID INTEGER PRIMARY KEY AUTOINCREMENT, PATH TEXT,PATH_ENCODED TEXT);",NULL,NULL,NULL));
		}
		int i4=(sqlite3_exec(db,"CREATE TABLE INCREMENTAL(ID INTEGER PRIMARY KEY AUTOINCREMENT,NAME TEXT,PATH TEXT,TIME INTEGER);",NULL,NULL,NULL));
		if(i4!=0)
		{
			WriteLogForlibmwshare(2,"Error in DatabaseOpen in sqlite3_exec in creating incremental  table" );
			//printf("ERROR CREATING BAACKUP TABLE:%d\n",__LINE__);
			sqlite3_close(db);
			exit(-1);
		}
		else
		{
			int ii4=(sqlite3_exec(db,"CREATE TABLE INCREMENTAL(ID INTEGER PRIMARY KEY AUTOINCREMENT,NAME TEXT,PATH TEXT,TIME INTEGER);",NULL,NULL,NULL));
		}
		


		//	WriteLogForlibmwshare(4,"All table created successfully" );
	}


	else
	{
		if(sqlite3_open("/tmpdata/escanAV/.backup.db",&db))
		{
			WriteLogForlibmwshare(2,"Error in DatabaseOpen in sqlite3_open in opening database" );
			//printf("error in oening backup.db:%d\n",__LINE__);
			sqlite3_close(db);
			exit(-1);
		}
	}	

	return 0;	
}



