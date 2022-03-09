#include<iostream>
#include<stdio.h>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sqlite3.h>
#include<signal.h>
#include"WriteLogForlibmwshare.h"
#include<dirent.h>
#include<pthread.h>
#include"ListFileRecursively_For_Tmpdata_Folder_Remove.h"
#include<signal.h>
#include<HandleSigint.h>
using namespace std;
/*list recursively remove the data from databse after removing the databse*/
extern sqlite3 *db;
extern int flag;
void ListFileRecursively_For_Tmpdata_Folder_Remove(char *basePath)
{
	//WriteLogForlibmwshare(2,"ListFileRecursively_For_Tmpdata_Folder_Remove started" );

	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
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
			//printf("%s\n",dp->d_name);


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
					WriteLogForlibmwshare(2,"Error in ListFileRecursively_For_Tmpdata_Folder_Remove in select data from tmpdata in sqlite3_prepare_v2 statement" );
					//printf("error in prepare v2=%d\n",__LINE__);
					sqlite3_close(db);
					exit(-1);
				}
				sqlite3_bind_text(res1,1,path,-1,NULL);
				if(sqlite3_step(res1)!=SQLITE_OK)
				{
					if(sqlite3_column_type(res1, 1) != SQLITE_NULL)
					{
						sqlite3_stmt *res2;
						if(sqlite3_prepare_v2(db,"DELETE FROM TMPDATA WHERE PATH=?",-1,&res2,NULL))
						{
							WriteLogForlibmwshare(2,"Error in ListFileRecursively_For_Tmpdata_Folder_Remove in delete data from tmpdata in sqlite3_prepare_v2 statement" );
							//printf("error=%d\n",__LINE__);
							sqlite3_close(db);
							exit(-1);
						}	
						sqlite3_bind_text(res2,1,path,-1,NULL);
						sqlite3_step(res2);

					}

				}
				//	sqlite3_reset(res1);


			}




			ListFileRecursively_For_Tmpdata_Folder_Remove(path);
		}
	}
	//WriteLogForlibmwshare(2,"ListFileRecursively_For_Tmpdata_Folder_Remove ended" );
	closedir(dir);

}


