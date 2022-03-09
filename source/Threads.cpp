#include<stdio.h>
#include<string.h>
#include<string>
#include<stdlib.h>
#include<unistd.h>
#include<sqlite3.h>
#include<signal.h>
#include<pthread.h>
#include"CopyFiles_fullbackup.h"
#include"ListFileRecursively_For_FullBackup.h"
#include"HandleSigint.h"
#include"Threads.h"
using namespace std;
/*all threads function+++++*/
/*ListFileRecursively_For_FullBackup*/
/*CopyFiles*/
extern sqlite3 *db;
extern int flag;
void *MyThreadFun1(void* ptrr5)
{
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	//WriteLogForlibmwshare(2,"MyThreadFun1 started" );
	ListFileRecursively_For_FullBackup((char *)ptrr5);
	//WriteLogForlibmwshare(2,"MyThreadFun1 ended" );
}


void *MyThreadFun2(void* ptrr5)
{
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	//WriteLogForlibmwshare(2,"MyThreadFun2 started" );
	CopyFiles_fullbackup((char *)ptrr5);
	//WriteLogForlibmwshare(2,"MyThreadFun2 ended" );

}

void *MyThreadFun3(void* ptrr5)
{
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	//WriteLogForlibmwshare(2,"MyThreadFun3 started" );
	ListFileRecursively_For_FullBackup((char *)ptrr5);
	//WriteLogForlibmwshare(2,"MyThreadFun3 ended" );
}


void *MyThreadFun4(void* ptrr5)
{
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	//WriteLogForlibmwshare(2,"MyThreadFun4 started" );
	CopyFiles_fullbackup((char *)ptrr5);
	//WriteLogForlibmwshare(2,"MyThreadFun4 ended" );

}

