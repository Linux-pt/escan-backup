#include<stdio.h>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include"HandleSigint.h"
#include<sys/stat.h>
#include<iostream>
#include"calculate_inode_number.h"
#include<sqlite3.h>
#include<signal.h>
using namespace std;
extern sqlite3 *db;
long calculate_inode_number(char *path)
{
	//WriteLogForlibmwshare(2,"calculate_inode_number started" );
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	struct stat file_stat;  
	int ret;
	ret=stat(path,&file_stat);
	long int inode= file_stat.st_ino;  // inode now contains inode number of the file with descriptor fd  
	//	printf("%d\n",inode);
	//WriteLogForlibmwshare(2,"calculate_inode_number ended" );
	return inode;
}


