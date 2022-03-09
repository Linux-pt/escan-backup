#include<stdio.h>
#include<string>
#include<string.h>
#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include <sys/statvfs.h>
#include<sqlite3.h>
#include"HandleSigint.h"
#include"FreeSpace.h"
using namespace std;
/*
 *function to calculate available spaces
 * */
extern sqlite3 *db;
unsigned long FreeSpace() 
{

	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	//WriteLogForlibmwshare(2,"FreeSpace started" );
	struct statvfs diskData;
	statvfs("/", &diskData);
	unsigned long available = diskData.f_bavail * diskData.f_bsize;
	//	long free_sp=(available+((1024*1024*1024)/2))/(1024*1024*1024);
	//printf("Free Space : %luG\n", free_sp);


	//WriteLogForlibmwshare(2,"FreeSpace ended" );
	return available;



}

