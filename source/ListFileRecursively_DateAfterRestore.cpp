#include<stdio.h>
#include<string.h>
#include<string>
#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<dirent.h>
#include"RestoreIncremental_For_BeforeAfter.h"
#include<sqlite3.h>
#include"HandleSigint.h"
#include"ListFileRecursively_DateAfterRestore.h"
using namespace std;
/*list all files for date after restore*/
/*DateAfterRestore*/
extern sqlite3 *db;
extern int flag;
void ListFileRecursively_DateAfterRestore(char *basePath,int val)
{
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	//WriteLogForlibmwshare(2,"ListFileRecursively_DateAfterRestore started" );
	char path[1024]="";
	struct dirent *dp;
	DIR *dir = opendir(basePath);

	if (!dir)
		return;

	while ((dp = readdir(dir)) != NULL && !flag)
	{
		if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
		{
			char f_name[1024];
			strcpy(f_name,dp->d_name);
			char *ptr; // declare a ptr pointer  
			ptr = strtok(dp->d_name, "_"); // use strtok() function to separate string using comma (,) delimiter. 
			char date[1024];
			strcpy(date,ptr);
			DateAfterRestore(date,f_name,val);



			strcpy(path, basePath);
			strcat(path, "/");
			strcat(path, dp->d_name);

			ListFileRecursively_DateAfterRestore(path,val);
		}
	}

	//WriteLogForlibmwshare(2,"ListFileRecursively_DateAfterRestore ended" );
	closedir(dir);
}
/*this function will restore all files*/
/*RestoreIncremental*/
void DateAfterRestore(char *tmpdata_date,char *unzip,int val)
{
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	//WriteLogForlibmwshare(2,"DateAfterRestore started" );

	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];
	time (&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer,sizeof(buffer),"%d-%m-%Y",timeinfo);


	char current_date[1024];
	strcpy(current_date,buffer);

	int current_day,current_month,current_year;
	int compare_day,compare_month,compare_year;
	int year,month,day;
	sscanf(current_date,"%d-%d-%d",&current_day,&current_month,&current_year); //reads the numbers







	struct tm date = { 0, 0, 12 } ;  // nominal time midday (arbitrary).

	date.tm_year = current_year - 1900 ;
	date.tm_mon = current_month - 1 ;  // note: zero indexed
	date.tm_mday = current_day ;       // note: not zero indexed

	struct tm* date1=&date;

	int d1,days;
	days=-val;
	const time_t ONE_DAY = 24*60*60 ;

	time_t date_seconds = mktime(date1)+(days*ONE_DAY);

	*date1 = *localtime(&date_seconds);

	char result_date[1024];
	int new_current_day=date.tm_mday;
	int new_current_mon=(date.tm_mon+1);	
	int new_current_year=(1900+date.tm_year);



	int t1_day,t1_month,t1_year;
	sscanf(tmpdata_date,"%d-%d-%d",&t1_day,&t1_month,&t1_year); //from the string
	if (t1_year>new_current_year || t1_month>new_current_mon || t1_day>=new_current_day) //compares 2 dates
	{
		RestoreIncremental_For_BeforeAfter(unzip);
	}

	//WriteLogForlibmwshare(2,"DateAfterRestore ended" );


}

