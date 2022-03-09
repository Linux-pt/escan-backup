#include<stdio.h>
#include<string.h>
#include<string>
#include<stdlib.h>
#include<iostream>
#include<signal.h>
//#include"As_Per_Time_Filename.h"
#include<fstream>
#include<sqlite3.h>
#include"WriteLogForlibmwshare.h"
#include<unistd.h>
#include"HandleSigint.h"
#include"Compare_File_Present_In_Backup.h"
#include"As_Per_Time_Filename.h"
#include"zip.h"
#include"encoded_path.h"
using namespace std;
/*MAJOR FUNCTION++*/
/*this funtion compare the files for incremental backup*/
/*in this file we actually compare file if present in tmpdata/escanAV/Backup file*/
extern sqlite3 *db;
/*
void Compare_File_Present_In_Backup(char *filename,char *file_name_path ,char *sha1sum,char *basepath)
{

	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	//WriteLogForlibmwshare(2,"Compare_File_Present_In_Backup started" );
	//printf("start of compare_file_preset_in_backup\n");
	char backup_filename[1024]="";
	char tmpdata_filename[1024]="";
	char backup_file_name_path[1024]="";
	char tmpdata_file_name_path[1024]="";
	char backup_sha1sum[1024]="";
	char tmpdata_sha1sum[1024]="";
	char current_path[1024]="";

	sqlite3_stmt *stmt;
	//	printf("selecting data froom backup\n");
	if(sqlite3_prepare_v2(db,"SELECT * FROM BACKUP WHERE PATH=?",-1,&stmt,NULL))
	{
		WriteLogForlibmwshare(2,"Error in Compare_File_Present_In_Backup in sqlite3_prepare_v2 while selecting data in backup table" );
		//	printf("error in prepare v2=%d \n",__LINE__);
		sqlite3_close(db);
		exit(-1);
	}	
	sqlite3_bind_text(stmt,1,file_name_path,-1,NULL);
	if(sqlite3_step(stmt)!=SQLITE_OK)
	{
		if(sqlite3_column_type(stmt,0)==SQLITE_NULL)
		{
			sqlite3_stmt *res4;
			//	printf("if null found out then inserting into it\n");
			if(sqlite3_prepare_v2(db,"INSERT INTO BACKUP VALUES(?,?,?,?);",-1,&res4,NULL))
			{
				WriteLogForlibmwshare(2,"Error in Compare_File_Present_In_Backup while inserting data in backup table" );
				//	printf("error=%d\n",__LINE__);
				sqlite3_close(db);
				exit(-1);
			}
			sqlite3_bind_text(res4,2,filename,-1,NULL);
			sqlite3_bind_text(res4,3,file_name_path,-1,NULL);
			sqlite3_bind_text(res4,4,sha1sum,-1,NULL);
			if(sqlite3_step(res4)!=SQLITE_DONE)
			{
				WriteLogForlibmwshare(2,"Error in Compare_File_Present_In_Backup in sqlite3_step" );
				//	printf("error=%d\n",__LINE__);
				sqlite3_close(db);
				exit(-1);
			}
		}
		else
		{
			//printf("loading data into 3 variables\n");
			strcpy(backup_filename,(const char *)sqlite3_column_text(stmt,1));				
			strcpy(backup_file_name_path,(const char *)sqlite3_column_text(stmt,2));				
			strcpy(backup_sha1sum,(const char *)sqlite3_column_text(stmt,3));				

		}
	}
	//	sqlite3_reset(stmt);


	//printf("starting actual comaparison\n");
	the actual comaparison we are doing here
	if(strcmp(filename,backup_filename)==0)
	{
		if(strcmp(file_name_path,backup_file_name_path)==0)
		{
			if(strcmp(sha1sum,backup_sha1sum)!=0)
			{

				sqlite3_stmt *res1;
				//printf("updating backup data before comaprison\n");
				if(sqlite3_prepare_v2(db,"UPDATE BACKUP SET SHA1SUM=? WHERE PATH=?",-1,&res1,NULL))
				{
					WriteLogForlibmwshare(2,"Error in Compare_File_Present_In_backup in update table backup in sqlite3_prepare_v2" );
					//	printf("error in prepare v2\n");
					sqlite3_close(db);
					exit(-1);
				}	
				sqlite3_bind_text(res1,1,sha1sum,-1,NULL);
				sqlite3_bind_text(res1,2,file_name_path,-1,NULL);
				sqlite3_step(res1);
				//	sqlite3_reset(res1);

				sqlite3_stmt *res3;
				//printf("selecting tmpdata\n");
				if(sqlite3_prepare_v2(db,"SELECT * FROM TMPDATA WHERE NAME=? AND SHA1SUM=?",-1,&res3,NULL))
				{
					WriteLogForlibmwshare(2,"Error in Compare_File_Present_In_Backup in sqlite3_prepare_v2 in select data from tmpdata" );
					//printf("error in prepare v2=%d\n",__LINE__);
					sqlite3_close(db);
					exit(-1);
				}
				sqlite3_bind_text(res3,1,filename,-1,NULL);
				sqlite3_bind_text(res3,2,backup_sha1sum,-1,NULL);
				//printf("am i here after selecting data\n");
				if(sqlite3_step(res3)!=SQLITE_OK)
				{

					if(sqlite3_column_type(res3,0)!=SQLITE_NULL)
					{
						strcpy(tmpdata_filename,(const char *)sqlite3_column_text(res3,1));				
						strcpy(tmpdata_file_name_path,(const char *)sqlite3_column_text(res3,2));				
						strcpy(tmpdata_sha1sum,(const char *)sqlite3_column_text(res3,3));				
					}
				}
				//	sqlite3_reset(res3);

				//printf("before_zip_comparison\n");
				if(strcmp(filename,tmpdata_filename)==0)
				{
					if(strcmp(backup_sha1sum,tmpdata_sha1sum)==0)
					{
						if(strcmp(sha1sum,tmpdata_sha1sum)!=0)
						{
							char buff[1024]="";
							char name_time[1024]="";
							strcpy(name_time,As_Per_Time_Filename().c_str());
							sprintf(buff,"/tmpdata/escanAV/escanIncremental/%s_%s.zip",name_time,tmpdata_filename);
							//	printf("STRING=%s\n\n",backup_file_name_path);
							//	sprintf(buff,"/tmpdata/escanAV/escanIncremental/%s-%s.zip",name_time,backup_file_name_path);
							printf("BUFF=%s\n\n\n",buff);

							struct zip_t *zip = zip_open(buff, ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
							zip_entry_open(zip, tmpdata_file_name_path);
							zip_entry_fwrite(zip, tmpdata_file_name_path);
							zip_entry_close(zip);	   
							zip_close(zip);

						}
					}
				} 
				//	printf("after zip comaprison\n");
			}
		}
	}
	//printf("end of Compare_File_Present_In_Backup\n");
	//WriteLogForlibmwshare(2,"Compare_File_Present_In_Backup ended" );
}	
*/


/*MAJOR FUNCTION++*/
/*this funtion compare the files for incremental backup*/
/*in this file we actually compare file if present in tmpdata/escanAV/Backup file*/
/*
void Compare_File_Present_In_Backup(char *filename,char *file_name_path ,char *sha1sum,char *basepath)
{

	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	//WriteLogForlibmwshare(2,"Compare_File_Present_In_Backup started" );
	//printf("start of compare_file_preset_in_backup\n");
	char backup_filename[1024]="";
	char tmpdata_filename[1024]="";
	char backup_file_name_path[1024]="";
	char tmpdata_file_name_path[1024]="";
	char backup_sha1sum[1024]="";
	char tmpdata_sha1sum[1024]="";
	char current_path[1024]="";

	sqlite3_stmt *stmt;
	//	printf("selecting data froom backup\n");
	if(sqlite3_prepare_v2(db,"SELECT * FROM BACKUP WHERE PATH=?",-1,&stmt,NULL))
	{
		WriteLogForlibmwshare(2,"Error in Compare_File_Present_In_Backup in sqlite3_prepare_v2 while selecting data in backup table" );
		//	printf("error in prepare v2=%d \n",__LINE__);
		sqlite3_close(db);
		exit(-1);
	}	
	sqlite3_bind_text(stmt,1,file_name_path,-1,NULL);
	if(sqlite3_step(stmt)!=SQLITE_OK)
	{
		if(sqlite3_column_type(stmt,0)==SQLITE_NULL)
		{
			sqlite3_stmt *res4;
			//	printf("if null found out then inserting into it\n");
			if(sqlite3_prepare_v2(db,"INSERT INTO BACKUP VALUES(?,?,?,?);",-1,&res4,NULL))
			{
				WriteLogForlibmwshare(2,"Error in Compare_File_Present_In_Backup while inserting data in backup table" );
				//	printf("error=%d\n",__LINE__);
				sqlite3_close(db);
				exit(-1);
			}
			sqlite3_bind_text(res4,2,filename,-1,NULL);
			sqlite3_bind_text(res4,3,file_name_path,-1,NULL);
			sqlite3_bind_text(res4,4,sha1sum,-1,NULL);
			if(sqlite3_step(res4)!=SQLITE_DONE)
			{
				WriteLogForlibmwshare(2,"Error in Compare_File_Present_In_Backup in sqlite3_step" );
				//	printf("error=%d\n",__LINE__);
				sqlite3_close(db);
				exit(-1);
			}
		}
		else
		{
			//printf("loading data into 3 variables\n");
			strcpy(backup_filename,(const char *)sqlite3_column_text(stmt,1));				
			strcpy(backup_file_name_path,(const char *)sqlite3_column_text(stmt,2));				
			strcpy(backup_sha1sum,(const char *)sqlite3_column_text(stmt,3));				

		}
	}
	//	sqlite3_reset(stmt);


	//printf("starting actual comaparison\n");
	//The actual comaparison we are doing here
	if(strcmp(filename,backup_filename)==0)
	{
		if(strcmp(file_name_path,backup_file_name_path)==0)
		{
			if(strcmp(sha1sum,backup_sha1sum)!=0)
			{

				sqlite3_stmt *res1;
				//printf("updating backup data before comaprison\n");
				if(sqlite3_prepare_v2(db,"UPDATE BACKUP SET SHA1SUM=? WHERE PATH=?",-1,&res1,NULL))
				{
					WriteLogForlibmwshare(2,"Error in Compare_File_Present_In_backup in update table backup in sqlite3_prepare_v2" );
					//	printf("error in prepare v2\n");
					sqlite3_close(db);
					exit(-1);
				}	
				sqlite3_bind_text(res1,1,sha1sum,-1,NULL);
				sqlite3_bind_text(res1,2,file_name_path,-1,NULL);
				sqlite3_step(res1);
				//	sqlite3_reset(res1);

				sqlite3_stmt *res3;
				//printf("selecting tmpdata\n");
				if(sqlite3_prepare_v2(db,"SELECT * FROM TMPDATA WHERE NAME=? AND SHA1SUM=?",-1,&res3,NULL))
				{
					WriteLogForlibmwshare(2,"Error in Compare_File_Present_In_Backup in sqlite3_prepare_v2 in select data from tmpdata" );
					//printf("error in prepare v2=%d\n",__LINE__);
					sqlite3_close(db);
					exit(-1);
				}
				sqlite3_bind_text(res3,1,filename,-1,NULL);
				sqlite3_bind_text(res3,2,backup_sha1sum,-1,NULL);
				//printf("am i here after selecting data\n");
				if(sqlite3_step(res3)!=SQLITE_OK)
				{

					if(sqlite3_column_type(res3,0)!=SQLITE_NULL)
					{
						strcpy(tmpdata_filename,(const char *)sqlite3_column_text(res3,1));				
						strcpy(tmpdata_file_name_path,(const char *)sqlite3_column_text(res3,2));				
						strcpy(tmpdata_sha1sum,(const char *)sqlite3_column_text(res3,3));				
					}
				}
				//	sqlite3_reset(res3);

				//printf("before_zip_comparison\n");
				if(strcmp(filename,tmpdata_filename)==0)
				{
					if(strcmp(backup_sha1sum,tmpdata_sha1sum)==0)
					{
						if(strcmp(sha1sum,tmpdata_sha1sum)!=0)
						{
							char buff[1024]="";
							char name_time[1024]="";
							char p_name[1024]="";
							long long int *ep1=(long long int *)malloc(100);
							//strcpy(name_time,As_Per_Time_Filename(p_name,ep1).c_str());
							As_Per_Time_Filename(p_name,ep1);

							//strcpy(name_time,As_Per_Time_Filename(p_name,ep1).c_str());
							sprintf(buff,"/tmpdata/escanAV/escanIncremental/%s_%s.zip",p_name,tmpdata_filename);
							//	printf("STRING=%s\n\n",backup_file_name_path);
							//	sprintf(buff,"/tmpdata/escanAV/escanIncremental/%s-%s.zip",name_time,backup_file_name_path);
							printf("BUFF=%s\n\n\n",buff);
							

							sqlite3_stmt *res20;
							if(sqlite3_prepare_v2(db,"INSERT INTO INCREMENTAL VALUES(?,?,?,?);",-1,&res20,NULL))
							{
								printf("error in prepare v2=%d\n",__LINE__);
								sqlite3_close(db);
								exit(-1);
							}
							sqlite3_bind_text(res20,2,buff,-1,NULL);
							sqlite3_bind_text(res20,3,backup_file_name_path,-1,NULL);
							
							
							//sqlite_bind_text(res20,4,*ep1,-1,NULL);	
							long long int k=*ep1;
							printf("k value=%lld\n",k);
							sqlite3_bind_double(res20,4,k);	
			
						
							sqlite3_step(res20);
							//	sqlite3_reset(res20);
						
							
							HZIP hz;
							hz = CreateZip( buff, 0 ); 
							ZipAdd(hz, tmpdata_file_name_path , "/tmpdata/escanAV/escanIncremental" );
							CloseZip(hz);
							
							struct zip_t *zip = zip_open(buff, ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
							zip_entry_open(zip, tmpdata_file_name_path);
							zip_entry_fwrite(zip, tmpdata_file_name_path);
							zip_entry_close(zip);	   
							zip_close(zip);
							
						}
					}
				} 
				//	printf("after zip comaprison\n");
			}
		}
	}
	//printf("end of Compare_File_Present_In_Backup\n");
	//WriteLogForlibmwshare(2,"Compare_File_Present_In_Backup ended" );
}	

*/

/*MAJOR FUNCTION++*/
/*this funtion compare the files for incremental backup*/
/*in this file we actually compare file if present in tmpdata/escanAV/Backup file*/
void Compare_File_Present_In_Backup(char *filename,char *file_name_path ,char *sha1sum,char *basepath)
{

	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	//WriteLogForlibmwshare(2,"Compare_File_Present_In_Backup started" );
	//printf("start of compare_file_preset_in_backup\n");
	char backup_filename[1024]="";
	char tmpdata_filename[1024]="";
	char backup_file_name_path[1024]="";
	char tmpdata_file_name_path[1024]="";
	char backup_sha1sum[1024]="";
	char tmpdata_sha1sum[1024]="";
	char current_path[1024]="";

	sqlite3_stmt *stmt;
	//	printf("selecting data froom backup\n");
	if(sqlite3_prepare_v2(db,"SELECT * FROM BACKUP WHERE PATH=?",-1,&stmt,NULL))
	{
		WriteLogForlibmwshare(2,"Error in Compare_File_Present_In_Backup in sqlite3_prepare_v2 while selecting data in backup table" );
		//	printf("error in prepare v2=%d \n",__LINE__);
		sqlite3_close(db);
		exit(-1);
	}	
	sqlite3_bind_text(stmt,1,file_name_path,-1,NULL);
	if(sqlite3_step(stmt)!=SQLITE_OK)
	{
		if(sqlite3_column_type(stmt,0)==SQLITE_NULL)
		{
			sqlite3_stmt *res4;
			//	printf("if null found out then inserting into it\n");
			if(sqlite3_prepare_v2(db,"INSERT INTO BACKUP VALUES(?,?,?,?);",-1,&res4,NULL))
			{
				WriteLogForlibmwshare(2,"Error in Compare_File_Present_In_Backup while inserting data in backup table" );
				//	printf("error=%d\n",__LINE__);
				sqlite3_close(db);
				exit(-1);
			}
			sqlite3_bind_text(res4,2,filename,-1,NULL);
			sqlite3_bind_text(res4,3,file_name_path,-1,NULL);
			sqlite3_bind_text(res4,4,sha1sum,-1,NULL);
			if(sqlite3_step(res4)!=SQLITE_DONE)
			{
				WriteLogForlibmwshare(2,"Error in Compare_File_Present_In_Backup in sqlite3_step" );
				//	printf("error=%d\n",__LINE__);
				sqlite3_close(db);
				exit(-1);
			}
		}
		else
		{
			//printf("loading data into 3 variables\n");
			strcpy(backup_filename,(const char *)sqlite3_column_text(stmt,1));				
			strcpy(backup_file_name_path,(const char *)sqlite3_column_text(stmt,2));				
			strcpy(backup_sha1sum,(const char *)sqlite3_column_text(stmt,3));				

		}
	}
	//	sqlite3_reset(stmt);


	//printf("starting actual comaparison\n");
	/*the actual comaparison we are doing here*/
	if(strcmp(filename,backup_filename)==0)
	{
		if(strcmp(file_name_path,backup_file_name_path)==0)
		{
			if(strcmp(sha1sum,backup_sha1sum)!=0)
			{

				sqlite3_stmt *res1;
				//printf("updating backup data before comaprison\n");
				if(sqlite3_prepare_v2(db,"UPDATE BACKUP SET SHA1SUM=? WHERE PATH=?",-1,&res1,NULL))
				{
					WriteLogForlibmwshare(2,"Error in Compare_File_Present_In_backup in update table backup in sqlite3_prepare_v2" );
					//	printf("error in prepare v2\n");
					sqlite3_close(db);
					exit(-1);
				}	
				sqlite3_bind_text(res1,1,sha1sum,-1,NULL);
				sqlite3_bind_text(res1,2,file_name_path,-1,NULL);
				sqlite3_step(res1);
				//	sqlite3_reset(res1);

				sqlite3_stmt *res3;
				//printf("selecting tmpdata\n");
				if(sqlite3_prepare_v2(db,"SELECT * FROM TMPDATA WHERE NAME=? AND SHA1SUM=?",-1,&res3,NULL))
				{
					WriteLogForlibmwshare(2,"Error in Compare_File_Present_In_Backup in sqlite3_prepare_v2 in select data from tmpdata" );
					//printf("error in prepare v2=%d\n",__LINE__);
					sqlite3_close(db);
					exit(-1);
				}
				sqlite3_bind_text(res3,1,filename,-1,NULL);
				sqlite3_bind_text(res3,2,backup_sha1sum,-1,NULL);
				//printf("am i here after selecting data\n");
				if(sqlite3_step(res3)!=SQLITE_OK)
				{

					if(sqlite3_column_type(res3,0)!=SQLITE_NULL)
					{
						strcpy(tmpdata_filename,(const char *)sqlite3_column_text(res3,1));				
						strcpy(tmpdata_file_name_path,(const char *)sqlite3_column_text(res3,2));				
						strcpy(tmpdata_sha1sum,(const char *)sqlite3_column_text(res3,3));				
					}
				}
				//	sqlite3_reset(res3);

				//printf("before_zip_comparison\n");
				if(strcmp(filename,tmpdata_filename)==0)
				{
					if(strcmp(backup_sha1sum,tmpdata_sha1sum)==0)
					{
						if(strcmp(sha1sum,tmpdata_sha1sum)!=0)
						{
							char buff[1024]="";
							char name_time[1024]="";
							char p_name[1024]="";
							long long int *ep1=(long long int *)malloc(100);
							//strcpy(name_time,As_Per_Time_Filename(p_name,ep1).c_str());
							As_Per_Time_Filename(p_name,ep1);

							//strcpy(name_time,As_Per_Time_Filename(p_name,ep1).c_str());
						
						
							//sprintf(buff,"/tmpdata/escanAV/escanIncremental/%s_%s.zip",p_name,tmpdata_filename);
							
							char inc_path[1024]="";
							strcpy(inc_path,encoded_path(backup_file_name_path).c_str());
							sprintf(buff,"/tmpdata/escanAV/escanIncremental/%s%s.zip",p_name,inc_path);

							//	printf("STRING=%s\n\n",backup_file_name_path);
							//		sprintf(buff,"/tmpdata/escanAV/escanIncremental/%s-%s.zip",name_time,backup_file_name_path);
							printf("BUFF=%s\n\n\n",buff);


							sqlite3_stmt *res20;
							if(sqlite3_prepare_v2(db,"INSERT INTO INCREMENTAL VALUES(?,?,?,?);",-1,&res20,NULL))
							{
								printf("error in prepare v2=%d\n",__LINE__);
								sqlite3_close(db);
								exit(-1);
							}
							sqlite3_bind_text(res20,2,buff,-1,NULL);
							sqlite3_bind_text(res20,3,backup_file_name_path,-1,NULL);


							//sqlite_bind_text(res20,4,*ep1,-1,NULL);	
							long long int k=*ep1;
							printf("k value=%lld\n",k);
							sqlite3_bind_double(res20,4,k);	


							sqlite3_step(res20);
							//	sqlite3_reset(res20);

							printf("zippping file\n");	
							HZIP hz;
							hz = CreateZip( buff, 0 ); 
							ZipAdd(hz, tmpdata_file_name_path , "/tmpdata/escanAV/escanIncremental" );
							CloseZip(hz);
							/*
							   struct zip_t *zip = zip_open(buff, ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
							   zip_entry_open(zip, tmpdata_file_name_path);
							   zip_entry_fwrite(zip, tmpdata_file_name_path);
							   zip_entry_close(zip);	   
							   zip_close(zip);
							   */
						}
					}
				} 
				//	printf("after zip comaprison\n");
			}
		}
	}
	//printf("end of Compare_File_Present_In_Backup\n");
	//WriteLogForlibmwshare(2,"Compare_File_Present_In_Backup ended" );
}	



