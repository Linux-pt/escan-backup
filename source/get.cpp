/************************************************ 

DEVELOPER:OMKAR PISE
TEAM:LINUX TEAM
START-DATE:25 OCT 2020
WORK:ESCAN-BACKUP

 *********************************************************/
/*making code optimize and making logic to store code on google drive*/
/*removing database from backup files------>>>>major work in linux*/
/*deleting files in linux*/
/*if segementation error occurs please check dangling error in linux*/

//LOG FILE---------->>>>>>>/var/MicroWorld/var/log/ebackup.log
//CONF FILE FOR EBACKUP-------------->>>>>>>>>>/opt/MicroWorld/etc/ebackup.conf


//int readConfiguration(const char *fileName, char *option, char *output);

//int writeConfiguration(const char *conffile, const char *key, const char *value)

//conf file will be from /opt/Microworld/etc/ebackup.conf

#include<unistd.h>
#include<pthread.h>
#include<signal.h>
#include <stdio.h>
#include <string.h>
#include<dirent.h>
#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<string>
#include <fstream> 
#include"zip.h"
//#include"miniz.h"------->THIS IS PRESENT IN LIBZIP LIBRARY
#include<time.h>
#include <sys/time.h>
#include<sqlite3.h>
#include <sys/statvfs.h>
#include<ftw.h>
#include"readConfiguration.h"
#include"writeConfiguration.h"
//#include"sfl.h"
//#include"getValueOfCommand.h"
using namespace std;



void ListFileRecursively_For_Tmpdata_Folder_Remove(char *basePath);
void ListFileRecursively_For_Backup_Folder_Remove(char *basePath);


void WriteLogForlibmwshare(short int reqDebugLevel, string logLine );

int DatabaseOpen();

unsigned long FreeSpace(); 
void HandleSigint(int sig);

//void ListFileRecursively_Check_Directory(char *basePath);
void RestoreIncremental(char *argv);

void DateBeforeRemove(char *tmpdata_date,char *unzip,int val);
void ListFileRecursively_DateBeforeRemove(char *basePath,int val);

void ListFileRecursively_MonthBeforeRemove(char *basePath,int val);
void MonthBeforeRemove(char *tmpdata_date,char *unzip,int val);

void YearBeforeRemove(char *tmpdata_date,char *unzip,int val);
void ListFileRecursively_YearBeforeRemove(char *basePath,int val);

void MonthBeforeRestore(char *tmpdata_date,char *unzip,int val);
void DateBeforeRestore(char *tmpdata_date,char *unzip,int );
void YearBeforeRestore(char *tmpdata_date,char *unzip,int );

void RestoreFolder(char *path);

void ListFileRecursively_DateBeforeRestore(char *basePath,int );
void ListFileRecursively_YearBeforeRestore(char *basePath,int );
void ListFileRecursively_MonthBeforeRestore(char *basePath,int );

int CreateFolder();

void ListFileRecursively_For_FullBackup(char *path);

void CopyFiles_fullbackup(char *);
void CopyFiles_incremental(char *);

void Read_BackupData();
void Read_Tmpdata();

string CalculateSha1sum(char *file_name_path);

void ListFileRecursively_For_Tmpdata(char *);
void ListFileRecursively_For_Compare(char *basePath);

void Compare_File_Present_In_Backup(char *filename,char *file_name_path ,char *sha1sum,char * basepath);

int On_Extract_Entry(const char *filename, void *arg); 

string As_Per_Time_Filename();

void Replace_String(char *);
void fileRemove(char *unzip);

void *MyThreadFun1(void* ptrr5);
void *MyThreadFun2(void* ptrr5);
void *MyThreadFun3(void* ptrr5);
void *MyThreadFun4(void* ptrr5);

void DateAfterRemove(char *tmpdata_date,char *unzip,int val);
void ListFileRecursively_DateAfterRemove(char *basePath,int val);

void ListFileRecursively_MonthAfterRemove(char *basePath,int val);
void MonthAfterRemove(char *tmpdata_date,char *unzip,int val);

void YearAfterRemove(char *tmpdata_date,char *unzip,int val);
void ListFileRecursively_YearAfterRemove(char *basePath,int val);


void MonthAfterRestore(char *tmpdata_date,char *unzip,int val);
void DateAfterRestore(char *tmpdata_date,char *unzip,int );
void YearAfterRestore(char *tmpdata_date,char *unzip,int );

void ListFileRecursively_DateAfterRestore(char *basePath,int );
void ListFileRecursively_YearAfterRestore(char *basePath,int );
void ListFileRecursively_MonthAfterRestore(char *basePath,int );


void ListFileRecursively_For_Tmpdata_Folder_Remove(char *basePath);
void ListFileRecursively_For_backup_Folder_Remove(char *basePath);



long long int GetDirectorySize(char *dir);
void PrintColumnValue(sqlite3_stmt* stmt, int col); 
static int remove_folder(const char *pathname, const struct stat *sbuf, int type, struct FTW *ftwb);
long calculate_inode_number(char *path);
/*check whether directory name exist in databse or not*/
/*if not exist then insert into path table*/
/*
   void ListFileRecursively_Check_Directory(char *basePath)
   {
//WriteLogForlibmwshare(2,"ListFileRecursively_Check_Directory started" );
signal(SIGINT, HandleSigint);
signal(SIGTERM, HandleSigint);
char path[1024]="";
struct dirent *dp;
DIR *dir = opendir(basePath);
char buff[1024]="";

// Unable to open directory stream
if (!dir)
return;

while ((dp = readdir(dir)) != NULL && !flag)
{
if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
{
strcpy(path, basePath);
strcat(path, "/");
strcat(path, dp->d_name);

if(dp->d_type==DT_DIR)
{		

sqlite3_stmt *res1;
if(sqlite3_prepare_v2(db,"SELECT * FROM PATH WHERE PATH=?",-1,&res1,NULL))
{
printf("error in prepare v2=%d\n",__LINE__);
sqlite3_close(db);
exit(-1);
}
sqlite3_bind_text(res1,1,path,-1,NULL);
if(sqlite3_step(res1)!=SQLITE_OK)
{
if(sqlite3_column_type(res1,0)==SQLITE_NULL)
{
sqlite3_stmt *res2;
if(sqlite3_prepare_v2(db,"INSERT INTO PATH VALUES(?,?);",-1,&res2,NULL))
{
printf("error in prepare v2=%d\n",__LINE__);
sqlite3_close(db);
exit(-1);
}
sqlite3_bind_text(res2,2,path,-1,NULL);
sqlite3_step(res2);
//	sqlite3_reset(res2);
}

}
}	

ListFileRecursively_Check_Directory(path);
}
}	

//WriteLogForlibmwshare(2,"ListFileRecursively_Check_Directory ended" );
closedir(dir);
}
*/


