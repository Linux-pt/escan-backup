#include<stdio.h>
#include<string.h>
#include<string>
#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<dirent.h>
#include"HandleSigint.h"
#include"ListFileRecursively_YearBeforeRemove.h"
#include<sqlite3.h>
using namespace std;


/*this function used to compare file name with before year*/
/*if condition becomes true then it will called yearbeforeremove function*/
/*in that function it will remove the file*/
/*YearBeforeRemove */
extern sqlite3 *db;
extern int flag;
void ListFileRecursively_YearBeforeRemove(char *basePath,int val)
{
	//WriteLogForlibmwshare(2,"ListFileRecursively_YearBeforeRemove started" );
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	char path[1024];
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
			YearBeforeRemove(date,f_name,val);



			// Construct new path from our base path
			strcpy(path, basePath);
			strcat(path, "/");
			strcat(path, dp->d_name);

			ListFileRecursively_YearBeforeRemove(path,val);
		}
	}

	//WriteLogForlibmwshare(2,"ListFileRecursively_YearBeforeRemove ended" );
	closedir(dir);
}
/*this file used to remove file if year was matched*/
void YearBeforeRemove(char *tmpdata_date,char *unzip,int val)
{

	//WriteLogForlibmwshare(2,"YearBeforeRemove started" );
	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);


	time_t rawtime;
	struct tm * timeinfo;
	char buffer[1024];
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

	int d1=0,days=0;
	d1=(val*365);
	days=(-d1);
	const time_t ONE_DAY = 24*60*60 ;

	time_t date_seconds = mktime(date1)+(days*ONE_DAY);

	*date1 = *localtime(&date_seconds);

	char result_date[1024];
	int new_current_day=date.tm_mday;
	int new_current_mon=(date.tm_mon+1);
	int new_current_year=(1900+date.tm_year);



	int t1_day,t1_month,t1_year;
	sscanf(tmpdata_date,"%d-%d-%d",&t1_day,&t1_month,&t1_year); //from the string
	if (t1_year<=new_current_year) //compares 2 dates
	{
		//	RestoreIncremental(unzip);

		char file_name_remove[1024];
		sprintf(file_name_remove,"/tmpdata/escanAV/escanIncremental/%s",unzip);
		remove(file_name_remove);


	}
	//WriteLogForlibmwshare(2,"YearBeforeRemove ended" );


}

