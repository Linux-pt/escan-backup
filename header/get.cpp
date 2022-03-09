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








//void ListFileRecursively_Check_Directory(char *basePath);














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


