#include<stdio.h>
#include<string.h>
#include<string>
#include<stdlib.h>
#include<unistd.h>
#include<iostream>
#include"CopyFiles_incremental.h"
#include<ftw.h>
#include"HandleSigint.h"
#include<sqlite3.h>
#include<signal.h>
#include"WriteLogForlibmwshare.h"
//#include"remove_folder.h"
#include"encoded_path.h"
using namespace std;

/*for copying data in full backup*/
/*HandleSigint*/
extern sqlite3 *db;
extern int flag;
/*
void CopyFiles_incremental(char *path)
{
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	//WriteLogForlibmwshare(2,"CopyFiles started" );
	char buff[1024];
	struct stat stats;
	stat(path,&stats);
	char sample_dir[1024]="my_testing_dir";

	char new_path[1024]="";
	sprintf(new_path,"/tmpdata/escanAV/Backup/%ld",stats.st_ino);

	if (nftw(new_path, remove_folder,10, FTW_DEPTH|FTW_MOUNT|FTW_PHYS) < 0)
	{
		WriteLogForlibmwshare(2,"Error in CopyFiles_incremental nftw" );
		perror("ERROR: ntfw");
		exit(1);
	}

	//int status = mkdir("/tmpdata/escanAV/Backup/my_testing_dir", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	//sprintf(buff,"cp -rf %s /tmpdata/escanAV/Backup/%s",path,sample_dir);
	sprintf(buff,"cp -rf %s /tmpdata/escanAV/Backup/%ld",path,stats.st_ino);
	system(buff);

	//WriteLogForlibmwshare(2,"CopyFiles ended" );

}
*/

static int remove_folder(const char *pathname, const struct stat *sbuf, int type, struct FTW *ftwb)
{
	//WriteLogForlibmwshare(2,"remove_folder started" );
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	if(remove(pathname) < 0)
	{
		WriteLogForlibmwshare(2,"Error in remove_folder function " );
		perror("ERROR: remove");
		return -1;
	}
	//WriteLogForlibmwshare(2,"remove_folder ended" );
	return 0;
}


/*for copying data in full backup*/
/*
void CopyFiles_incremental(char *path)
{
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	//WriteLogForlibmwshare(2,"CopyFiles started" );
	char buff[1024];
	struct stat stats;
	stat(path,&stats);
	char sample_dir[1024]="my_testing_dir";

	char encode_path[1024]="";
	strcpy(encode_path,encoded_path(path).c_str());
	
	char new_path[1024]="";
	sprintf(new_path,"/tmpdata/escanAV/Backup/%s",encode_path);

	if (nftw(new_path, remove_folder,10, FTW_DEPTH|FTW_MOUNT|FTW_PHYS) < 0)
	{
		WriteLogForlibmwshare(2,"Error in CopyFiles_incremental nftw" );
		perror("ERROR: ntfw");
		exit(1);
	}
//int status = mkdir("/tmpdata/escanAV/Backup/my_testing_dir", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	//sprintf(buff,"cp -rf %s /tmpdata/escanAV/Backup/%s",path,sample_dir);
	sprintf(buff,"cp -rf %s /tmpdata/escanAV/Backup/%s",path,encode_path);
	system(buff);

	//WriteLogForlibmwshare(2,"CopyFiles ended" );

}

*/

/*for copying data in full backup*/
void CopyFiles_incremental(char *path)
{
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	//WriteLogForlibmwshare(2,"CopyFiles started" );
	char buff[1024];
	struct stat stats;
	stat(path,&stats);
	char sample_dir[1024]="my_testing_dir";

	char encode_path[1024]="";
	strcpy(encode_path,encoded_path(path).c_str());
	
	char new_path[1024]="";
	sprintf(new_path,"/tmpdata/escanAV/Backup/%s",encode_path);

	if (nftw(new_path, remove_folder,10, FTW_DEPTH|FTW_MOUNT|FTW_PHYS) < 0)
	{
		WriteLogForlibmwshare(2,"Error in CopyFiles_incremental nftw" );
		perror("ERROR: ntfw");
		exit(1);
	}
//int status = mkdir("/tmpdata/escanAV/Backup/my_testing_dir", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	//sprintf(buff,"cp -rf %s /tmpdata/escanAV/Backup/%s",path,sample_dir);
	sprintf(buff,"cp -rf %s /tmpdata/escanAV/Backup/%s",path,encode_path);
	system(buff);

	//WriteLogForlibmwshare(2,"CopyFiles ended" );

}


