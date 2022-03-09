#include<stdio.h>
#include<iostream>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<signal.h>
#include<sqlite3.h>
#include"WriteLogForlibmwshare.h"
#include<unistd.h>
#include"CalculateSha1sum.h"
#include"HandleSigint.h"
using namespace std;
/*calculate sha1sum of file of given path*/
/*we are using system command here*/
/*be aware it can error also if command was not present*/
/*present in /usr/bin/sha1sum*/
extern sqlite3 *db;
string CalculateSha1sum(char *file_name_path)
{
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	//WriteLogForlibmwshare(2,"CalculateSha1sum started" );
	char str[1024];
	FILE *fpipe,*fp;
	sprintf(str,"sha1sum '%s'",file_name_path);
	char command[1024]="";
	strcpy(command ,str);
	char c = 0;

	if (0 == (fpipe = (FILE*)popen(command, "r")))
	{
		WriteLogForlibmwshare(2,"Error in CalculateSha1sum " );
		//perror("popen() failed.");
		exit(EXIT_FAILURE);
	}
	char str1[1024];
	if( fgets (str1, 60, fpipe)!=NULL )
	{
		//	printf("sha1number//\\ is : \t%s",str1);
	}
	pclose(fpipe);

	char arr[1024];
	char *ptr; // declare a ptr pointer  
	ptr = strtok(str1," "); // use strtok() function to separate string using comma (,) delimiter.  
	strcpy(arr,ptr);
	//WriteLogForlibmwshare(2,"CalculateSha1sum ended" );

	//	pclose(fpipe);
	return arr;

}

