#include<stdio.h>
#include<string>
#include<string.h>
#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<sqlite3.h>
#include"HandleSigint.h"
using namespace std;
extern sqlite3 *db;
extern int flag;
string encoded_path(char * path)
{

signal(SIGINT, HandleSigint);
signal(SIGTERM, HandleSigint);

	char actualpath8 [1024]="";
	char *ptrr8;

	ptrr8 = realpath(path, actualpath8);

	string s(ptrr8);

	for(int i=0;i<s.length();i++)
	{
		if(s[0]=='/')
		{
			s[i]='_';
		}
		if(s[i]=='/')
		{
			s[i]='-';
		}
	}
	return s;
//	printf("%s\n",s.c_str());

}



