#include<stdio.h>
#include<iostream>
#include<string>
#include<signal.h>
#include<sqlite3.h>
#include"WriteLogForlibmwshare.h"
#include<dirent.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include"ListFileRecursively_For_Tmpdata.h"
#include"CalculateSha1sum.h"
#include"HandleSigint.h"
using namespace std;
/*list recursively the data from tmpdata and enter into tmpdata table in backup db*/
/*CalculateSha1sum*/
extern sqlite3 *db;
extern int flag;
void ListFileRecursively_For_Tmpdata(char *basePath)
{
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	//WriteLogForlibmwshare(2,"ListFileRecursively_For_Tmpdata started" );

	char path[1024]="";
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


			//struct stat s;

			if((dp->d_type==DT_SOCK) || (dp->d_type==DT_BLK) || (dp->d_type==DT_CHR) || (dp->d_type==DT_FIFO) || (dp->d_type==DT_LNK) || (dp->d_type==DT_UNKNOWN))
			{		
				continue;
			}

			if(dp->d_type==DT_REG)
			{

				char n1[1024]="";
				sqlite3_stmt *res1;
				if(sqlite3_prepare_v2(db,"SELECT * FROM TMPDATA WHERE PATH=?",-1,&res1,NULL))
				{
					WriteLogForlibmwshare(2,"Error in ListFileRecursively_For_Tmpdata in sqlite3 prepare v2 statement" );
					//printf("error in prepare v2=%d\n",__LINE__);
					sqlite3_close(db);
					exit(-1);
				}
				sqlite3_bind_text(res1,1,path,-1,NULL);
				if(sqlite3_step(res1)!=SQLITE_OK)
				{
					if(sqlite3_column_type(res1, 1) == SQLITE_NULL)
					{
						sqlite3_stmt *stmt;
						if(sqlite3_prepare_v2(db,"INSERT INTO TMPDATA VALUES(?,?,?,?)",-1,&stmt,NULL))
						{
							WriteLogForlibmwshare(2,"Error in ListFileRecursively_For_Tmpdata in sqlite3_prepare_v2 after sqlite3_column_typei while inserting data" );
							//	printf("error in prepare v2=%d\n",__LINE__);
							sqlite3_close(db);
							exit(-1);
						}	
						char name[1024]="";
						strcpy(name,CalculateSha1sum(path).c_str());

						sqlite3_bind_text(stmt,2,dp->d_name,-1,NULL);
						sqlite3_bind_text(stmt,3,path,-1,NULL);
						//	sqlite3_bind_text(stmt,4,CalculateSha1sum(path).c_str(),-1,NULL);
						sqlite3_bind_text(stmt,4,name,-1,NULL);

						sqlite3_step(stmt);
						//	sqlite3_reset(stmt);
					}
					else
					{
						char sha1[1024]="";	
						strcpy(sha1,(const char *)sqlite3_column_text(res1,3));
						char sha2[1024]="";
						strcpy(sha2,CalculateSha1sum(path).c_str());
						if(strcmp(sha1,sha2)!=0)
						{
							sqlite3_stmt *res2;
							if(sqlite3_prepare_v2(db,"DELETE FROM TMPDATA WHERE PATH=?",-1,&res2,NULL))
							{
								WriteLogForlibmwshare(2,"Error in sqlite3_prepare_v2 in ListFileRecursively_For_Tmpdata after CalculateSha1sumi in delete data from tmpdata" );
								//printf("error=%d\n",__LINE__);
								sqlite3_close(db);
								exit(-1);
							}	
							sqlite3_bind_text(res2,1,path,-1,NULL);
							sqlite3_step(res2);

							sqlite3_stmt *res3;
							if(sqlite3_prepare_v2(db,"INSERT INTO TMPDATA VALUES(?,?,?,?);",-1,&res3,NULL))
							{
								WriteLogForlibmwshare(2,"Error in sqlite3_prepare_v2 in inserting data in tmpdata values in function ListFileRecursively_For_Tmpdata" );
								printf("error in prepare v2i=%d\n",__LINE__);
								sqlite3_close(db);
								exit(-1);


							}
							sqlite3_bind_text(res3,2,dp->d_name,-1,NULL);
							sqlite3_bind_text(res3,3,path,-1,NULL);
							sqlite3_bind_text(res3,4,sha2,-1,NULL);

							sqlite3_step(res3);
						}

					}
					//	sqlite3_reset(res1);

				}
			}




			ListFileRecursively_For_Tmpdata(path);
		}
	}
	//WriteLogForlibmwshare(2,"ListFileRecursively_For_Tmpdata ended" );
	closedir(dir);

}



