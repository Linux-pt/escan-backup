#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string>
#include<string.h>
#include<iostream>
#include<dirent.h>
#include<sqlite3.h>
#include"CalculateSha1sum.h"
#include"ListFileRecursively_For_FullBackup.h"
#include"HandleSigint.h"
#include"WriteLogForlibmwshare.h"
#include<signal.h>
using namespace std;

/*this is for full-backup*/
/*it will maintain databse of backup table*/
/*CalculateSha1sum*/
/*HandleSigint*/
extern sqlite3 *db;
extern int flag;
/*
void ListFileRecursively_For_FullBackup(char *basePath)
{
	signal(SIGTERM, HandleSigint);
	signal(SIGINT, HandleSigint);
	//WriteLogForlibmwshare(2,"ListFileRecursively_For_FullBackup was start" );
	char path[1024];
	struct dirent *dp;
	DIR *dir = opendir(basePath);
	if (!dir)
	{
		return;
	}
	while ((dp = readdir(dir)) != NULL && !flag)
	{
		if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
		{
			strcpy(path, basePath);
			strcat(path, "/");
			strcat(path, dp->d_name);
			printf("%s\n",dp->d_name);


			//			if((dp->d_type==DT_SOCK) || (dp->d_type==DT_BLK) || (dp->d_type==DT_CHR) || (dp->d_type==DT_FIFO) || (dp->d_type==DT_LNK) || (dp->d_type==DT_UNKNOWN && access(path,R_OK)!=0))

			we have to check for socket also because we cant calculate the sha1sum of socket thats why
			if((dp->d_type==DT_SOCK) || (dp->d_type==DT_BLK) || (dp->d_type==DT_CHR) || (dp->d_type==DT_FIFO) || (dp->d_type==DT_LNK) || (dp->d_type==DT_UNKNOWN))
			{

				continue;
			}

			if(dp->d_type==DT_REG && dp->d_type!=DT_DIR)
			{


				sqlite3_stmt *res1;
				if(sqlite3_prepare_v2(db,"SELECT * FROM PATH WHERE PATH=?;",-1,&res1,NULL))
				{
					WriteLogForlibmwshare(2,"Error in select backup in path table sqlite3_prepare_v2 in ListFileRecursively_For_FullBackup" );
					//printf("error=%d\n",__LINE__);
					sqlite3_close(db);
					exit(-1);
				}
				sqlite3_bind_text(res1,1,path,-1,NULL);
				if path was not exist then it will entered into db and then it will perform backup
				if(sqlite3_step(res1)!=SQLITE_OK)
				{
					if(sqlite3_column_type(res1,1)==SQLITE_NULL)
					{
						//	sqlite3_reset(res1);

						sqlite3_stmt *stmt=NULL;
						if(sqlite3_prepare_v2(db,"INSERT INTO BACKUP VALUES(?,?,?,?)",-1,&stmt,NULL))
						{
							WriteLogForlibmwshare(2,"Error in inseting data in backup in ListFileRecursively_For_FullBackup function" );
							//	printf("error in prepare v2=%d\n",__LINE__);
							sqlite3_close(db);
							exit(-1);
						}	

						sqlite3_bind_text(stmt,2,dp->d_name,-1,NULL);
						sqlite3_bind_text(stmt,3,path,-1,NULL);
						//sqlite3_bind_text(stmt,4,"sha1sum",-1,NULL);
						char name[1024];
						strcpy(name,CalculateSha1sum(path).c_str());
						sqlite3_bind_text(stmt,4,name,-1,NULL);
						//	char inode_data[1024]="";
						//	strcpy(inode_data,(const char *)calculate_inode_number(path));
						//	sqlite3_bind_text(stmt,5,inode_data,-1,NULL);
						//sqlite3_bind_text(stmt,5,name,-1,NULL);

						sqlite3_step(stmt);
						//	sqlite3_reset(stmt);

					}
				}


			}

			ListFileRecursively_For_FullBackup(path);
		}
	}
	closedir(dir);
	//WriteLogForlibmwshare(2,"ListFileRecursively_For_FullBackup was ended" );
}
*/

/*this is for full-backup*/
/*it will maintain databse of backup table*/
/*CalculateSha1sum*/

void ListFileRecursively_For_FullBackup(char *basePath)
{
	signal(SIGTERM, HandleSigint);
	signal(SIGINT, HandleSigint);
	//WriteLogForlibmwshare(2,"ListFileRecursively_For_FullBackup was start" );
	char path[1024];
	struct dirent *dp;
	DIR *dir = opendir(basePath);
	if (!dir)
	{
		return;
	}
	while ((dp = readdir(dir)) != NULL && !flag)
	{
		if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
		{
			strcpy(path, basePath);
			strcat(path, "/");
			strcat(path, dp->d_name);
			printf("%s\n",dp->d_name);


			//			if((dp->d_type==DT_SOCK) || (dp->d_type==DT_BLK) || (dp->d_type==DT_CHR) || (dp->d_type==DT_FIFO) || (dp->d_type==DT_LNK) || (dp->d_type==DT_UNKNOWN && access(path,R_OK)!=0))

			/*we have to check for socket also because we cant calculate the sha1sum of socket thats why*/
			if((dp->d_type==DT_SOCK) || (dp->d_type==DT_BLK) || (dp->d_type==DT_CHR) || (dp->d_type==DT_FIFO) || (dp->d_type==DT_LNK) || (dp->d_type==DT_UNKNOWN))
			{

				continue;
			}

			if(dp->d_type==DT_REG && dp->d_type!=DT_DIR)
			{

				char name[1024]="";

				sqlite3_stmt *res1;
				if(sqlite3_prepare_v2(db,"SELECT * FROM PATH WHERE PATH=?;",-1,&res1,NULL))
				{
					WriteLogForlibmwshare(2,"Error in select backup in path table sqlite3_prepare_v2 in ListFileRecursively_For_FullBackup" );
					//printf("error=%d\n",__LINE__);
					sqlite3_close(db);
					exit(-1);
				}
				sqlite3_bind_text(res1,1,path,-1,NULL);
				/*if path was not exist then it will entered into db and then it will perform backup*/
				if(sqlite3_step(res1)!=SQLITE_OK)
				{
					if(sqlite3_column_type(res1,1)==SQLITE_NULL)
					{
						//	sqlite3_reset(res1);


						char n1[1024]="";


						sqlite3_stmt *stmt=NULL;
						if(sqlite3_prepare_v2(db,"INSERT INTO BACKUP VALUES(?,?,?,?)",-1,&stmt,NULL))
						{
							WriteLogForlibmwshare(2,"Error in inseting data in backup in ListFileRecursively_For_FullBackup function" );
							//	printf("error in prepare v2=%d\n",__LINE__);
							sqlite3_close(db);
							exit(-1);
						}	
						sqlite3_bind_text(stmt,2,dp->d_name,-1,NULL);
						sqlite3_bind_text(stmt,3,path,-1,NULL);
						//sqlite3_bind_text(stmt,4,"sha1sum",-1,NULL);
						char name[1024];
						strcpy(name,CalculateSha1sum(path).c_str());
						sqlite3_bind_text(stmt,4,name,-1,NULL);
						//	char inode_data[1024]="";
						//	strcpy(inode_data,(const char *)calculate_inode_number(path));
						//	sqlite3_bind_text(stmt,5,inode_data,-1,NULL);
						//sqlite3_bind_text(stmt,5,name,-1,NULL);

						sqlite3_step(stmt);
						//	sqlite3_reset(stmt);

					}
				}


			}

			ListFileRecursively_For_FullBackup(path);
		}
	}
	closedir(dir);
	//WriteLogForlibmwshare(2,"ListFileRecursively_For_FullBackup was ended" );
}


