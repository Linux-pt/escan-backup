#include<stdio.h>
#include<string.h>
#include<string>
#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include"Compare_File_Present_In_Backup.h"
#include<dirent.h>
#include<sqlite3.h>
#include"CalculateSha1sum.h"
#include"ListFileRecursively_For_Compare.h"
#include"HandleSigint.h"
using namespace std;
/*for every file it will call Compare_File_Present_In_Backup this function*/
/*Compare_File_Present_In_Backup*/
/*CalculateSha1sum*/
extern sqlite3 *db;
extern int flag;
void ListFileRecursively_For_Compare(char *basePath)
{
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	//WriteLogForlibmwshare(2,"ListFileRecursively_For_Compare started" );
	char path[1024]="";
	struct dirent *dp;
	DIR *dir = opendir(basePath);
	//char sha1[1024]="";
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

			if((dp->d_type==DT_SOCK) || (dp->d_type==DT_BLK) || (dp->d_type==DT_CHR) || (dp->d_type==DT_FIFO) || (dp->d_type==DT_LNK) || (dp->d_type==DT_UNKNOWN))
			{		
				continue;
			}

			if(dp->d_type==DT_REG)
			{
				char sha1[1024]="";
				strcpy(sha1,CalculateSha1sum(path).c_str());
				Compare_File_Present_In_Backup(dp->d_name,path,sha1,basePath);
			}
			ListFileRecursively_For_Compare(path);
		}
	}
	//WriteLogForlibmwshare(2,"ListFileRecursively_For_Compare ended" );
	closedir(dir);

}


