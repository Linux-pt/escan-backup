#include<stdio.h>
#include<string.h>
#include<string>
#include<signal.h>
#include<dirent.h>
#include<dirent.h>
#include<sqlite3.h>
#include<sys/stat.h>
#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include"GetDirectorySize.h"
#include"HandleSigint.h"
using namespace std;
extern sqlite3 *db;
extern int flag;
long long int GetDirectorySize(char *dir)
{
	//WriteLogForlibmwshare(2,"GetDirectorySize started" );
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	long long int totalSize=0;
	if ((dp = opendir(dir)) == NULL)
	{
		//	fprintf(stderr, "Cannot open dir: %s\n", dir);

		return 0; // It could be a file , Or the directory doesn't exist 
	}
	// Add the size of your own directory first 
	lstat(dir, &statbuf);
	totalSize+=statbuf.st_size;
	while ((entry = readdir(dp)) != NULL && !flag)
	{
		char subdir[1024];
		sprintf(subdir, "%s/%s", dir, entry->d_name);
		lstat(subdir, &statbuf);




		if (S_ISDIR(statbuf.st_mode))
		{
			if ((strcmp(".", entry->d_name) ==0)  ||  (strcmp("..", entry->d_name) ==0) )
			{
				continue;
			}
			long long int subDirSize = GetDirectorySize(subdir);
			totalSize+=subDirSize;
		}
		else
		{
			totalSize+=statbuf.st_size;
		}
	}
	closedir(dp);
	//WriteLogForlibmwshare(2,"GetDirectorySize ended" );
	return totalSize;
}


