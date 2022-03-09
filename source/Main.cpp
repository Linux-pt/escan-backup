#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<unistd.h>
#include<sqlite3.h>
#include<fstream>
#include"Main.h"
#include"WriteLogForlibmwshare.h"
#include"FreeSpace.h"
#include"readConfiguration.h"
#include"CreateFolder.h"
#include"DatabaseOpen.h"
#include"GetDirectorySize.h"
#include"Threads.h"
#include"ListFileRecursively_For_Tmpdata.h"
#include"ListFileRecursively_For_Compare.h"
#include"CopyFiles_incremental.h"
#include"RestoreIncremental.h"
#include"RestoreFolder.h"

#include"ListFileRecursively_DateBeforeRestore.h"
#include"ListFileRecursively_MonthBeforeRestore.h"
#include"ListFileRecursively_YearBeforeRestore.h"

#include"ListFileRecursively_DateAfterRestore.h"
#include"ListFileRecursively_MonthAfterRestore.h"
#include"ListFileRecursively_YearAfterRestore.h"


#include"ListFileRecursively_DateBeforeRemove.h"
#include"ListFileRecursively_MonthBeforeRemove.h"
#include"ListFileRecursively_YearBeforeRemove.h"

#include"ListFileRecursively_DateAfterRemove.h"
#include"ListFileRecursively_MonthAfterRemove.h"
#include"ListFileRecursively_YearAfterRemove.h"

#include"Read_Data.h"
#include"HandleSigint.h"
#include"fileRemove.h"
#include"encoded_path.h"
using namespace std;

sqlite3 *db;
int flag=0;
int main(int argc,char *argv[])
{
	WriteLogForlibmwshare(2,"FreeSpace called" );
	long int free_space_value=FreeSpace();
	WriteLogForlibmwshare(2,"FreeSpace execution completed" );

	if(free_space_value> 1000000000)
	{			
		WriteLogForlibmwshare(2,"FreeSpace execution completed and u have enough space so u can do backup" );
	}	
	else
	{
		WriteLogForlibmwshare(2,"U dont have enough space for backup" );
		return 1;
	}
	/*creating folder if not exists*/
	char cValue[1024]="";
		if(readConfiguration((char *)"/opt/Microworld/etc/ebackup.conf",(char *)"ebackup:status",cValue)==0 && atoi(cValue)==1)
		{
		//printf("%s\n",cValue);	
		}		
		


	WriteLogForlibmwshare(2,"CreateFolder called" );
	if(CreateFolder()==0)
	{
		//WriteLogForlibmwshare(4,"Create function was executed successfully" );
	}
	else
	{
		WriteLogForlibmwshare(4,"CreateFolder function was failed" );	
	}
	WriteLogForlibmwshare(2,"CreateFolder execution completed" );



	/*checking whether backup present or not if not then return -1*/
	/*else return something else*/
	if(DatabaseOpen()==0)
	{		
		//	WriteLogForlibmwshare(4,"Database return value was 0" );
	}
	else
	{		
		WriteLogForlibmwshare(4,"Database Open Failed" );
	}


	signal(SIGINT, HandleSigint);
	signal(SIGTERM, HandleSigint);
	char backup_path[1024]="/tmpdata/escanAV/Backup";
	char buff[1024]="";
	int n;
	if(argc<2)
	{
		/*
		   printf("\n");
		   printf("[-F][-FOLDER-NAME][--FOR-FULL-BACKUP]\n");
		   printf("[-I][-FOLDER-NAME][--FOR-INCREMENTAL-BACKUP]\n");
		   printf("[-r][-FILE-NAME-AS-PER-TMPDATA][--FOR-FILE-RESTORE]\n");
		   printf("[-d][-FILE-NAME-AS-PER-TMPDATA][--FOR-FILE-REMOVE]\n");
		//	printf("[-D][-FOLDER-NAME][--FOR-FOLDER-REMOVE]\n");	
		printf("[-R][-FOLDER-NAME][--FOR-FOLDER-RESTORE]\n");
		printf("[-RBD][-BEFORE-DATE-COUNT][--FOR-RESTORE-FILES-BEFORE-DATE]\n");
		printf("[-RBM][-BEFORE-MONTH-COUNT][--FOR-RESTORE-FILES-BEFORE-MONTH]\n");
		printf("[-RBY][-BEFORE-YEAR-COUNT][--FOR-RESTORE-FILES-BEFORE-YEAR]\n");

		printf("[-DBD][-BEFORE-DATE-COUNT][--FOR-REMOVE-FILES-BEFORE-DATE]\n");
		printf("[-DBM][-BEFORE-MONTH-COUNT][--FOR-REMOVE-FILES-BEFORE-DATE]\n");
		printf("[-DBY][-BEFORE-YEAR-COUNT][--FOR-REMOVE-FILES-BEFORE-YEAR]\n");


		printf("[-RAD][-AFTER-DATE-COUNT][--FOR-RESTORE-FILES-AFTER-DATE]\n");
		printf("[-RAM][-AFTER-MONTH-COUNT][--FOR-RESTORE-FILES-AFTER-MONTH]\n");
		printf("[-RAY][-AFTER-YEAR-COUNT][--FOR-RESTORE-FILES-AFTER-YEAR]\n");


		printf("[-DAD][-AFTER-DATE-COUNT][--FOR-REMOVE-FILES-AFTER-DATE]\n");
		printf("[-DAM][-AFTER-MONTH-COUNT][--FOR-REMOVE-FILES-AFTER-DATE]\n");
		printf("[-DAY][-AFTER-YEAR-COUNT][--FOR-REMOVE-FILES-AFTER-YEAR]\n");
		printf("[-INFO][-READ-DATA-FROM-TMPDATA][-READ-DATA-FROM-BACKUP]\n");	
		printf("[-H][-HELP]\n");
		printf("\n");
		*/

		printf("\n");
		printf("[escan-backup][-F][-FOLDER-NAME][--FOR-FULL-BACKUP]\n");
		printf("[escan-backup][-I][-FOLDER-NAME][--FOR-INCREMENTAL-BACKUP]\n");
		printf("[escan-backup][-r][-FILE-NAME-AS-PER-TMPDATA][--FOR-FILE-RESTORE]\n");
		printf("[escan-backup][-d][-FILE-NAME-AS-PER-TMPDATA][--FOR-FILE-REMOVE]\n");
		//	printf("[-D][-FOLDER-NAME][--FOR-FOLDER-REMOVE]\n");	
		printf("[escan-backup][-R][-FOLDER-NAME][--FOR-FOLDER-RESTORE]\n");
		printf("[escan-backup][-RBD][-BEFORE-DATE-COUNT][--FOR-RESTORE-FILES-BEFORE-DATE]\n");
		printf("[escan-backup][-RBM][-BEFORE-MONTH-COUNT][--FOR-RESTORE-FILES-BEFORE-MONTH]\n");
		printf("[escan-backup][-RBY][-BEFORE-YEAR-COUNT][--FOR-RESTORE-FILES-BEFORE-YEAR]\n");

		printf("[escan-backup][-DBD][-BEFORE-DATE-COUNT][--FOR-REMOVE-FILES-BEFORE-DATE]\n");
		printf("[escan-backup][-DBM][-BEFORE-MONTH-COUNT][--FOR-REMOVE-FILES-BEFORE-DATE]\n");
		printf("[escan-backup][-DBY][-BEFORE-YEAR-COUNT][--FOR-REMOVE-FILES-BEFORE-YEAR]\n");


		printf("[escan-backup][-RAD][-AFTER-DATE-COUNT][--FOR-RESTORE-FILES-AFTER-DATE]\n");
		printf("[escan-backup][-RAM][-AFTER-MONTH-COUNT][--FOR-RESTORE-FILES-AFTER-MONTH]\n");
		printf("[escan-backup][-RAY][-AFTER-YEAR-COUNT][--FOR-RESTORE-FILES-AFTER-YEAR]\n");


		printf("[escan-backup][-DAD][-AFTER-DATE-COUNT][--FOR-REMOVE-FILES-AFTER-DATE]\n");
		printf("[escan-backup][-DAM][-AFTER-MONTH-COUNT][--FOR-REMOVE-FILES-AFTER-DATE]\n");
		printf("[escan-backup][-DAY][-AFTER-YEAR-COUNT][--FOR-REMOVE-FILES-AFTER-YEAR]\n");
		printf("[[escan-backup]-INFO][-READ-DATA-FROM-TMPDATA][-READ-DATA-FROM-BACKUP]\n");	
		printf("[escan-backup][-H][-HELP]\n");
		printf("\n");





	}


	/*for full backup*/
	if(argc>=2)
	{
		WriteLogForlibmwshare(4,"Backup is Starting" );
		if(strcmp(argv[1],"-F")==0 || strcmp(argv[1],"--FOR-FULL-BACKUP")==0)
		{
			struct stat stats;
			WriteLogForlibmwshare(4,"Full backup is started" );
			long int total=0;
			/*calculating the file storage in all command line argument*/

			WriteLogForlibmwshare(2,"GetDirectorySize called" );
			for(int i=2;i<argc;i++)
			{
				total +=GetDirectorySize(argv[i]);

			}
			WriteLogForlibmwshare(2,"GetDirectorySize execution completed" );
			/*here we are checking whether the remaining size was greater than approximately 1GB*/
			/*if it is size of remaining will be greater than 1 GB then it will return that do full backup*/
			/*else size are not available*/
			if((free_space_value-1000000000)>total)
			{

				//printf("free_space_values=%ld\n",(free_space_value));
				//printf("free_space_values=%ld\n",(free_space_value-1000000000));
				//printf("total_directory_size=%ld\n",total);
				FILE *r1;
				char path[1024]="";
				int i;
				for(i=2;i<argc;i++)
				{
					strcpy(path,argv[i]);

					char actualpath8 [1024]="";
					char *ptrr8;

					ptrr8 = realpath(path, actualpath8);


					struct stat sb;	
					if (lstat(argv[i], &sb) == -1) {
						WriteLogForlibmwshare(1,"lstat error" );
						perror("lstat");
						exit(EXIT_FAILURE);
					}

					/*checking if it directory or not inside that we are entering into path backup*/
					if((sb.st_mode & S_IFMT)==S_IFDIR)
					{
						if(ptrr8!=NULL)
						{
							sqlite3_stmt *res1;
							if(sqlite3_prepare_v2(db,"SELECT * FROM PATH WHERE PATH=?;",-1,&res1,NULL))
							{
								WriteLogForlibmwshare(4,"Error in prepare V2 in full backup in main" );
								//	printf("error in prepare v2=%d\n",__LINE__);
								sqlite3_close(db);
								exit(-1);
							}

							sqlite3_bind_text(res1,1,ptrr8,-1,NULL);
							/**/
							if(sqlite3_step(res1)!=SQLITE_OK)
							{
								/*checking that full backup are already present or not*/
								/*if not then return NULL else it will continue*/
								if(sqlite3_column_type(res1, 0) == SQLITE_NULL)
								{
									/*
									   sqlite3_stmt *res2;
									   if(sqlite3_prepare_v2(db,"INSERT INTO PATH VALUES(?,?);",-1,&res2,NULL)){
									   printf("error in prepare v2=%d \n",__LINE__);
									   sqlite3_close(db);
									   exit(-1);
									   }
									   sqlite3_bind_text(res2,2,ptrr3,-1,NULL);
									   if(sqlite3_step(res2)!=SQLITE_DONE){
									   printf("error in sqlite_step res=%d\n",__LINE__);
									   sqlite3_close(db);
									   exit(-1);
									   }
									   */
									pthread_t t1;

									WriteLogForlibmwshare(2,"Thread_1 ListFileRecursively_For_FullBackup  called" );
									pthread_create(&t1, NULL, MyThreadFun1, (void *)ptrr8);
									WriteLogForlibmwshare(2,"Thread_1 ListFileRecursively_For_FullBackup execution was completed" );
									// pthread_join(t1, NULL);


									pthread_t t2;
									WriteLogForlibmwshare(2,"Thread_2 CopyFiles  called" );
									pthread_create(&t2, NULL, MyThreadFun2, (void *)ptrr8);
									WriteLogForlibmwshare(2,"Thread_2 CopyFiles  execution was completed" );
									pthread_join(t2, NULL);
									pthread_join(t1,NULL);


									//	ListFileRecursively_For_FullBackup(ptrr8);
									//	CopyFiles(ptrr8);

									sqlite3_stmt *res3;
									/*	if(sqlite3_exec(db,"DELETE FROM TMPDATA",NULL,NULL,NULL))
										{
										printf("error in executing query=%d\n",__LINE__);
										sqlite3_close(db);
										exit(-1);
										}
										*/

									/*for inserting full backup data into tmpdata table in backup*/
									WriteLogForlibmwshare(2,"ListFileRecursively_For_Tmpdata called" );
									ListFileRecursively_For_Tmpdata(backup_path);
									WriteLogForlibmwshare(2,"ListFileRecursively_For_Tmpdata execution completed" );

									/*for inserting directory name in path table in backup*/
									//	WriteLogForlibmwshare(2,"ListFileRecursively_Check_Directory called" );
									//	ListFileRecursively_Check_Directory(ptrr8);
									//	WriteLogForlibmwshare(2,"ListFileRecursively_Check_Directory execution completed" );

									sqlite3_stmt *res2;
									if(sqlite3_prepare_v2(db,"INSERT INTO PATH VALUES(?,?,?);",-1,&res2,NULL))
									{
										WriteLogForlibmwshare(2,"Error in inserting data in path table in main after ListFileRecursively_For_Tmpdata fn " );
										//printf("error in prepare v2=%d \n",__LINE__);
										sqlite3_close(db);
										exit(-1);
									}
									sqlite3_bind_text(res2,2,ptrr8,-1,NULL);
									char enc_path1[1024]="";
									strcpy(enc_path1,(const char *)encoded_path(ptrr8).c_str());
									sqlite3_bind_text(res2,3,enc_path1,-1,NULL);
								/*	if(stat(ptrr8,&stats)==0)
									{
										sqlite3_bind_int(res2,3,stats.st_ino);
									}
								*/
									//sqlite3_bind_int(res2,3,123,-1,NULL);
									//sqlite3_bind_int(res2,3,123);

									if(sqlite3_step(res2)!=SQLITE_DONE)
									{
										WriteLogForlibmwshare(2,"Error in sqlite3_step in main after ListFileRecursively_For_Tmpdata fn" );
										//printf("error in sqlite_step res=%d\n",__LINE__);
										sqlite3_close(db);
										exit(-1);
									}
									//	sqlite3_reset(res2);
									//	sqlite3_reset(res1);	

								}

								else
								{
									//	int count=0;


									sqlite3_stmt *res4;
									if(sqlite3_prepare_v2(db,"SELECT * FROM PATH WHERE PATH=?",-1,&res4,NULL))
									{
										WriteLogForlibmwshare(2,"Error in sqlite3_prepare_v2 in main in else condition" );
										//	printf("error in executing prepare v2=%d\n",__LINE__);
										sqlite3_close(db);
										exit(-1);
									}
									sqlite3_bind_text(res4,1,ptrr8,-1,NULL);

									char buff1[1024]="";
									if(sqlite3_step(res4)!=SQLITE_OK)
									{
										if(sqlite3_column_type(res4,0)==SQLITE_NULL)
										{

											//	sqlite3_reset(res4);


											pthread_t t3;
											printf("Before Thread\n");
											WriteLogForlibmwshare(2,"Thread_3 ListFileRecursively_For_FullBackup  called" );
											pthread_create(&t3, NULL, MyThreadFun3, (void *)ptrr8);
											WriteLogForlibmwshare(2,"Thread_3 ListFileRecursively_For_FullBackup  execution was completed" );
											printf("after Thread\n");
											pthread_join(t3, NULL);


											pthread_t t4;
											printf("Before Thread\n");
											WriteLogForlibmwshare(2,"Thread_4 CopyFiles  called" );
											pthread_create(&t4, NULL, MyThreadFun4, (void *)ptrr8);
											WriteLogForlibmwshare(2,"Thread_4 COpyFiles execution was completed" );
											printf("after Thread\n");
											pthread_join(t4, NULL);


											//	ListFileRecursively_For_FullBackup(ptrr8);
											//	CopyFiles(ptrr8);

											/*	if(sqlite3_exec(db,"DELETE FROM TMPDATA",NULL,NULL,NULL))
												{
												printf("error in executing query=%d\n",__LINE__);
												sqlite3_close(db);
												exit(-1);
												}

*/											/*for inserting tmpdata records in tmpdata table in backup*/	
											WriteLogForlibmwshare(2,"ListFileRecursively_For_Tmpdata called" );
											ListFileRecursively_For_Tmpdata(backup_path);
											WriteLogForlibmwshare(2,"ListFileRecursively_For_Tmpdata execution completed" );

											/*for inserting records in path table in backup*/
											//	WriteLogForlibmwshare(2,"ListFileRecursively_Check_Directory called" );
											//	ListFileRecursively_Check_Directory(ptrr8);
											//	WriteLogForlibmwshare(2,"ListFileRecursively_Check_Directory execution was completed" );

											sqlite3_stmt *res5;
											if(sqlite3_prepare_v2(db,"INSERT INTO PATH VALUES(?,?,?);",-1,&res5,NULL))
											{
												WriteLogForlibmwshare(2,"Error in sqlite3_prepare_v2 in main after ListFileRecursively_For_Tmpdata function" );
												//	printf("error in prepare v2=%d \n",__LINE__);
												sqlite3_close(db);
												exit(-1);
											}
											sqlite3_bind_text(res5,2,ptrr8,-1,NULL);
											char enc_path2[1024]="";
											strcpy(enc_path2,(const char *)encoded_path(ptrr8).c_str());
											sqlite3_bind_text(res5,3,enc_path2,-1,NULL);
										/*	if(stat(ptrr8,&stats)==0)
											{
												sqlite3_bind_int(res5,3,stats.st_ino);
											}
										*/

											if(sqlite3_step(res5)!=SQLITE_DONE)
											{
												WriteLogForlibmwshare(2,"Error in sqlite3_step in main after ListFileRecursively_For_Tmpdata  this funcction " );
												//printf("error in sqlite_step res=%d\n",__LINE__);
												sqlite3_close(db);
												exit(-1);
											}
											//	sqlite3_reset(res5);



										}
									}

								}
							}
						}
					}
				}
			}
			else
			{
				WriteLogForlibmwshare(3,"Storage capacity was not enough thats why backup was not happened" );
				printf("U DONT HAVE STORAGE CAPACITY\n");

			}

			sqlite3_close(db);



		}
		if(strcmp(argv[1],"-I")==0 || strcmp(argv[1],"--FOR-INCREMENTAL-BACKUP")==0)
		{
			WriteLogForlibmwshare(4,"Incremental backup was happened" );
			long int total1=0;
			/*calculating the size of all incremental backup because incremental backup size is equal to file size */

			WriteLogForlibmwshare(2,"GetDirectorySize called" );
			for(int i1=2;i1<argc;i1++)
			{
				total1 +=GetDirectorySize(argv[i1]);

			}
			WriteLogForlibmwshare(2,"execution completed" );
			/*here also we check for table databse because incremental backup is also == full backup size*/
			if((free_space_value-1000000000)>total1)
			{
				printf("free_space_values=%ld\n",(free_space_value-1000000000));
				printf("total_directory_size=%ld\n",total1);

				int j;
				char buff5[1024]="";
				for(j=2;j<argc;j++)
				{

					int count10=0;
					char buff10[1024]="";

					char actualpath10[1024];
					char *ptrr10;

					ptrr10 = realpath(argv[j], actualpath10);
					sqlite3_stmt *res6;	
					if(sqlite3_prepare_v2(db,"SELECT * FROM PATH WHERE PATH=?;",-1,&res6,NULL))
					{
						WriteLogForlibmwshare(2,"Error in sqlite3_prepare_v2 in incremental backup at starting" );
						printf("error in executing prepare v2=%d\n",__LINE__);
						sqlite3_close(db);
						exit(-1);
					}
					sqlite3_bind_text(res6,1,ptrr10,-1,NULL);

					if(sqlite3_step(res6)!=SQLITE_OK)
					{
						if(sqlite3_column_type(res6,0)==SQLITE_NULL)
						{
							WriteLogForlibmwshare(4,"First Performed Incremental backup" );
							printf("first do full backup\n");	
						}
						else
						{

							//	sqlite3_reset(res6);

							WriteLogForlibmwshare(2,"ListFileRecursively_For_Compare called" );
							ListFileRecursively_For_Compare(ptrr10);
							WriteLogForlibmwshare(2,"ListFileRecursively_For_Compare execution was completed" );

							/*if(sqlite3_exec(db,"DELETE FROM TMPDATA;",NULL,NULL,NULL))
							  {
							  printf("error in exec=%d",__LINE__);
							  sqlite3_close(db);
							  exit(-1);
							  }
							  */	


							/*copying the data of directory*/
							WriteLogForlibmwshare(2,"CopyFiles called" );
							CopyFiles_incremental(ptrr10);
							WriteLogForlibmwshare(2,"CopyFiles execution was completed" );

							/*for inserting the records in tmpdata table*/
							WriteLogForlibmwshare(2,"ListFileRecursively_For_Tmpdata called" );
							ListFileRecursively_For_Tmpdata(backup_path);
							WriteLogForlibmwshare(2,"ListFileRecursively_For_Tmpdata execution was completed" );
						}

					}

				}
			}
			else
			{
				/*if it is less than 1GB then it will get an not enough space here*/
				WriteLogForlibmwshare(4,"U are not having enough space for incremental backup" );
				printf("U DONT HAVE ENOUGH SPACE FOR BACKUP\n");
			}
			sqlite3_close(db);

		}




		if(strcmp(argv[1],"-r")==0 || strcmp(argv[1],"--FOR-FILE-RESTORE")==0)
		{
			WriteLogForlibmwshare(4,"File was restoring" );
			for(int k=2;k<argc;k++)
			{
				char buff100[1024]="";

					char actualpath100[1024];
					char *ptrr100;

					ptrr100 = realpath(argv[k], actualpath100);
					
				WriteLogForlibmwshare(2,"RestoreIncremental called" );
				RestoreIncremental(ptrr100);			
				WriteLogForlibmwshare(2,"RestoreIncremental execution was completed" );

			}
			WriteLogForlibmwshare(4,"File restoration completed" );
			sqlite3_close(db);
		}			
		if(strcmp(argv[1],"-R")==0 || strcmp(argv[1],"--FOR-FOLDER-RESTORE")==0)
		{
			WriteLogForlibmwshare(4,"Folder was restoring" );
			for(int k=2;k<argc;k++)
			{

				WriteLogForlibmwshare(2,"RestoreFolder called" );
				RestoreFolder(argv[k]);
				WriteLogForlibmwshare(2,"RestoreFolder execution was completed" );
			}
			WriteLogForlibmwshare(4,"Folder restoration completed" );
			sqlite3_close(db);

		}
		/*	if(strcmp(argv[1],"-D")==0 || strcmp(argv[1],"--FOR-FOLDER-REMOVE")==0)
			{
			WriteLogForlibmwshare(4,"Folder was removing" );
			for folder removing we are using ftw it is usefull for file traversing in linux
			char Remove_Folder_Path_Data[1024]="";
		//	sprintf(Remove_Folder_Path_Data,"/tmpdata/escanAV/Backup/%s",argv[1]);
		//	ListFileRecursively_For_Tmpdata_Folder_Remove(Remove_Folder_Path_Data);
		for(int k=2;k<argc;k++)
		{
		char new_path[1024]="";
		sprintf(new_path,"/tmpdata/escanAV/Backup/%s",argv[k]);

		if (nftw(new_path, remove_folder,10, FTW_DEPTH|FTW_MOUNT|FTW_PHYS) < 0)
		{
		perror("ERROR: ntfw");
		exit(1);
		}


		}
		WriteLogForlibmwshare(4,"Folder was removed from Backup folder" );
		sqlite3_close(db);

		}
		*/
		if(strcmp(argv[1],"-RBD")==0 || strcmp(argv[1],"--FOR-RESTORE-FILES-BEFORE-DATE")==0)
		{
			WriteLogForlibmwshare(4,"Files was restoring before date" );
			int value=atoi(argv[2]);				
			char p1[1024]="/tmpdata/escanAV/escanIncremental/";
			WriteLogForlibmwshare(2,"ListFileRecursively_DateBeforeRestore called" );
			ListFileRecursively_DateBeforeRestore(p1,value);
			WriteLogForlibmwshare(2,"ListFileRecursively_DateBeforeRestore execution was completed" );
			sqlite3_close(db);
			WriteLogForlibmwshare(4,"Files was restoring before date was completed" );
		}
		if(strcmp(argv[1],"-RBM")==0 || strcmp(argv[1],"--FOR-RESTORE-FILES-BEFORE-MONTH")==0)
		{
			WriteLogForlibmwshare(4,"Files restore before month was started" );
			int value1=atoi(argv[2]);				
			char p2[1024]="/tmpdata/escanAV/escanIncremental/";
			WriteLogForlibmwshare(2,"ListFileRecursively_MonthBeforeRestore called" );
			ListFileRecursively_MonthBeforeRestore(p2,value1);
			WriteLogForlibmwshare(2,"ListFileRecursively_MonthBeforeRestore execution was completed" );
			sqlite3_close(db);
			WriteLogForlibmwshare(4,"Files restore before month was ended" );

		}
		if(strcmp(argv[1],"-RBY")==0 || strcmp(argv[1],"--FOR-RESTORE-FILES-BEFORE-YEAR")==0)
		{
			WriteLogForlibmwshare(4,"Files restore before year was started" );
			int value2=atoi(argv[2]);				
			char p3[1024]="/tmpdata/escanAV/escanIncremental/";
			WriteLogForlibmwshare(2,"ListFileRecursively_YearBeforeRestore called" );
			ListFileRecursively_YearBeforeRestore(p3,value2);
			WriteLogForlibmwshare(2,"ListFileRecursively_YearBeforeRestore execution was completed" );
			sqlite3_close(db);
			WriteLogForlibmwshare(4,"Files restore before year was ended" );
		}

		if(strcmp(argv[1],"-d")==0 || strcmp(argv[1],"--FOR-FILE-REMOVE")==0)
		{		
			WriteLogForlibmwshare(4,"Files remove was started" );
			for(int k=2;k<argc;k++)
			{
				fileRemove(argv[k]);
			}
			sqlite3_close(db);
			WriteLogForlibmwshare(4,"Files remove was ended" );
		}


		if(strcmp(argv[1],"-DBD")==0 || strcmp(argv[1],"--FOR-REMOVE-FILES-BEFORE-DATE")==0)
		{
			WriteLogForlibmwshare(4,"Files remove before date was started" );
			int value11=atoi(argv[2]);
			char p11[1024]="/tmpdata/escanAV/escanIncremental/";
			WriteLogForlibmwshare(2,"ListFileRecursively_DateBeforeRemove called" );
			ListFileRecursively_DateBeforeRemove(p11,value11);
			WriteLogForlibmwshare(2,"ListFileRecursively_DateBeforeRemove execution was completed" );
			sqlite3_close(db);
			WriteLogForlibmwshare(4,"Files remove before date was ended" );
		}
		if(strcmp(argv[1],"-DBM")==0 || strcmp(argv[1],"--FOR-REMOVE-FILES-BEFORE-MONTH")==0)
		{
			WriteLogForlibmwshare(4,"Files remove before month was started" );
			int value22=atoi(argv[2]);
			char p22[1024]="/tmpdata/escanAV/escanIncremental/";
			WriteLogForlibmwshare(2,"ListFileRecursively_MonthBeforeRemove called" );
			ListFileRecursively_MonthBeforeRemove(p22,value22);
			WriteLogForlibmwshare(2,"ListFileRecursively_MonthBeforeRemove execution was completed" );
			sqlite3_close(db);
			WriteLogForlibmwshare(4,"Files remove before month was ended" );

		}
		if(strcmp(argv[1],"-DBY")==0 || strcmp(argv[1],"--FOR-REMOVE-FILES-BEFORE-YEAR")==0)
		{
			WriteLogForlibmwshare(4,"Files remove before year was started" );
			int value33=atoi(argv[2]);
			char p33[1024]="/tmpdata/escanAV/escanIncremental/";
			WriteLogForlibmwshare(2,"ListFileRecursively_YearBeforeRemove called" );
			ListFileRecursively_YearBeforeRemove(p33,value33);
			WriteLogForlibmwshare(2,"ListFileRecursively_YearBeforeRemove called" );
			sqlite3_close(db);
			WriteLogForlibmwshare(4,"Files remove before year was ended" );
		}
		if(strcmp(argv[1],"-RAD")==0 || strcmp(argv[1],"--FOR-RESTORE-FILES-AFTER-DATE")==0)
		{
			WriteLogForlibmwshare(4,"Files restore after date was started" );
			int value=atoi(argv[2]);				
			char p1[1024]="/tmpdata/escanAV/escanIncremental/";
			WriteLogForlibmwshare(2,"ListFileRecursively_DateAfterRestore called" );
			ListFileRecursively_DateAfterRestore(p1,value);
			WriteLogForlibmwshare(2,"ListFileRecursively_DateAfterRestore execution was completed" );
			sqlite3_close(db);
			WriteLogForlibmwshare(4,"Files restore after date was ended" );
		}
		if(strcmp(argv[1],"-RAM")==0 || strcmp(argv[1],"--FOR-RESTORE-FILES-AFTER-MONTH")==0)
		{
			WriteLogForlibmwshare(4,"Files restore after month was started" );
			int value1=atoi(argv[2]);				
			char p2[1024]="/tmpdata/escanAV/escanIncremental/";
			WriteLogForlibmwshare(2,"ListFileRecursively_MonthAfterRestore called" );
			ListFileRecursively_MonthAfterRestore(p2,value1);
			WriteLogForlibmwshare(2,"ListFileRecursively_MonthAfterRestore execution was completed" );
			sqlite3_close(db);
			WriteLogForlibmwshare(4,"Files restore after month was ended" );

		}
		if(strcmp(argv[1],"-RAY")==0 || strcmp(argv[1],"--FOR-RESTORE-FILES-AFTER-YEAR")==0)
		{
			WriteLogForlibmwshare(4,"Files restore after year was started" );
			int value2=atoi(argv[2]);				
			char p3[1024]="/tmpdata/escanAV/escanIncremental/";
			WriteLogForlibmwshare(2,"ListFileRecursively_YearAfterRestore called" );
			ListFileRecursively_YearAfterRestore(p3,value2);
			WriteLogForlibmwshare(2,"ListFileRecursively_YearAfterRestore execution was completed" );
			sqlite3_close(db);
			WriteLogForlibmwshare(4,"Files restore after year was ended" );
		}



		if(strcmp(argv[1],"-DAD")==0 || strcmp(argv[1],"--FOR-REMOVE-FILES-AFTER-DATE")==0)
		{
			WriteLogForlibmwshare(4,"Files remove after date was started" );
			int value11=atoi(argv[2]);
			char p11[1024]="/tmpdata/escanAV/escanIncremental/";
			WriteLogForlibmwshare(2,"ListFileRecursively_DateAfterRemove called" );
			ListFileRecursively_DateAfterRemove(p11,value11);
			WriteLogForlibmwshare(2,"ListFileRecursively_DateAfterRemove execution was completed" );
			sqlite3_close(db);
			WriteLogForlibmwshare(4,"Files remove after date was ended" );
		}
		if(strcmp(argv[1],"-DAM")==0 || strcmp(argv[1],"--FOR-REMOVE-FILES-AFTER-MONTH")==0)
		{
			WriteLogForlibmwshare(4,"Files remove after month was started" );
			int value22=atoi(argv[2]);
			char p22[1024]="/tmpdata/escanAV/escanIncremental/";
			WriteLogForlibmwshare(2,"ListFileRecursively_MonthAfterRemove called" );
			ListFileRecursively_MonthAfterRemove(p22,value22);
			WriteLogForlibmwshare(2,"ListFileRecursively_MonthAfterRemove execution was completed" );
			sqlite3_close(db);
			WriteLogForlibmwshare(4,"Files remove after month was ended" );

		}
		if(strcmp(argv[1],"-DAY")==0 || strcmp(argv[1],"--FOR-REMOVE-FILES-AFTER-YEAR")==0)
		{
			WriteLogForlibmwshare(4,"Files remove after year was started" );
			int value33=atoi(argv[2]);
			char p33[1024]="/tmpdata/escanAV/escanIncremental/";
			WriteLogForlibmwshare(2,"ListFileRecursively_YearAfterRemove called" );
			ListFileRecursively_YearAfterRemove(p33,value33);
			WriteLogForlibmwshare(2,"ListFileRecursively_YearAfterRemove execution was completed" );
			sqlite3_close(db);
			WriteLogForlibmwshare(4,"Files remove after year was ended" );
		}
		if(strcmp(argv[1],"-INFO")==0)
		{
			WriteLogForlibmwshare(4,"Information started" );
			//int value33=atoi(argv[2]);
			//char p33[1024]="/tmpdata/escanAV/escanIncremental/";
			//ListFileRecursively_YearAfterRemove(p33,value33);
			Read_Tmpdata();
			Read_BackupData();	
			sqlite3_close(db);
			WriteLogForlibmwshare(4,"Information ended" );
		}




		if(strcmp(argv[1],"-H")==0 || strcmp(argv[1],"-HELP")==0)
		{
			WriteLogForlibmwshare(4,"Help started" );

			printf("\n");
			printf("[escan-backup][-F][-FOLDER-NAME][--FOR-FULL-BACKUP]\n");
			printf("[escan-backup][-I][-FOLDER-NAME][--FOR-INCREMENTAL-BACKUP]\n");
			printf("[escan-backup][-r][-FILE-NAME-AS-PER-TMPDATA][--FOR-FILE-RESTORE]\n");
			printf("[escan-backup][-d][-FILE-NAME-AS-PER-TMPDATA][--FOR-FILE-REMOVE]\n");
			//	printf("[-D][-FOLDER-NAME][--FOR-FOLDER-REMOVE]\n");	
			printf("[escan-backup][-R][-FOLDER-NAME][--FOR-FOLDER-RESTORE]\n");
			printf("[escan-backup][-RBD][-BEFORE-DATE-COUNT][--FOR-RESTORE-FILES-BEFORE-DATE]\n");
			printf("[escan-backup][-RBM][-BEFORE-MONTH-COUNT][--FOR-RESTORE-FILES-BEFORE-MONTH]\n");
			printf("[escan-backup][-RBY][-BEFORE-YEAR-COUNT][--FOR-RESTORE-FILES-BEFORE-YEAR]\n");

			printf("[escan-backup][-DBD][-BEFORE-DATE-COUNT][--FOR-REMOVE-FILES-BEFORE-DATE]\n");
			printf("[escan-backup][-DBM][-BEFORE-MONTH-COUNT][--FOR-REMOVE-FILES-BEFORE-DATE]\n");
			printf("[escan-backup][-DBY][-BEFORE-YEAR-COUNT][--FOR-REMOVE-FILES-BEFORE-YEAR]\n");


			printf("[escan-backup][-RAD][-AFTER-DATE-COUNT][--FOR-RESTORE-FILES-AFTER-DATE]\n");
			printf("[escan-backup][-RAM][-AFTER-MONTH-COUNT][--FOR-RESTORE-FILES-AFTER-MONTH]\n");
			printf("[escan-backup][-RAY][-AFTER-YEAR-COUNT][--FOR-RESTORE-FILES-AFTER-YEAR]\n");


			printf("[escan-backup][-DAD][-AFTER-DATE-COUNT][--FOR-REMOVE-FILES-AFTER-DATE]\n");
			printf("[escan-backup][-DAM][-AFTER-MONTH-COUNT][--FOR-REMOVE-FILES-AFTER-DATE]\n");
			printf("[escan-backup][-DAY][-AFTER-YEAR-COUNT][--FOR-REMOVE-FILES-AFTER-YEAR]\n");
			printf("[[escan-backup]-INFO][-READ-DATA-FROM-TMPDATA][-READ-DATA-FROM-BACKUP]\n");	
			printf("[escan-backup][-H][-HELP]\n");
			printf("\n");


			/*

			   printf("\n");
			   printf("[-F][-FOLDER-NAME][--FOR-FULL-BACKUP]\n");
			   printf("[-I][-FOLDER-NAME][--FOR-INCREMENTAL-BACKUP]\n");
			   printf("[-r][-FILE-NAME-AS-PER-TMPDATA][--FOR-FILE-RESTORE]\n");
			   printf("[-R][-FOLDER-NAME][--FOR-FOLDER-RESTORE]\n");
			//printf("[-D][-FOLDER-NAME][--FOR-FOLDER-REMOVE]\n");	
			printf("[-d][-FILE-NAME-AS-PER-TMPDATA][--FOR-FILE-REMOVE]\n");
			printf("[-RBD][-BEFORE-DATE-COUNT][--FOR-RESTORE-FILES-BEFORE-DATE]\n");
			printf("[-RBM][-BEFORE-MONTH-COUNT][--FOR-RESTORE-FILES-BEFORE-MONTH]\n");
			printf("[-RBY][-BEFORE-YEAR-COUNT][--FOR-RESTORE-FILES-BEFORE-YEAR]\n");

			printf("[-DBD][-BEFORE-DATE-COUNT][--FOR-REMOVE-FILES-BEFORE-DATE]\n");
			printf("[-DBM][-BEFORE-MONTH-COUNT][--FOR-REMOVE-FILES-BEFORE-DATE]\n");
			printf("[-DBY][-BEFORE-YEAR-COUNT][--FOR-REMOVE-FILES-BEFORE-YEAR]\n");


			printf("[-RAD][-AFTER-DATE-COUNT][--FOR-RESTORE-FILES-AFTER-DATE]\n");
			printf("[-RAM][-AFTER-MONTH-COUNT][--FOR-RESTORE-FILES-AFTER-MONTH]\n");
			printf("[-RAY][-AFTER-YEAR-COUNT][--FOR-RESTORE-FILES-AFTER-YEAR]\n");


			printf("[-DAD][-AFTER-DATE-COUNT][--FOR-REMOVE-FILES-AFTER-DATE]\n");
			printf("[-DAM][-AFTER-MONTH-COUNT][--FOR-REMOVE-FILES-AFTER-DATE]\n");
			printf("[-DAY][-AFTER-YEAR-COUNT][--FOR-REMOVE-FILES-AFTER-YEAR]\n");
			printf("[-INFO][-READ-DATA-FROM-TMPDATA][-READ-DATA-FROM-BACKUP]\n");
			printf("[-H][-HELP]\n");
			printf("\n");

*/

			//			printf("\n[-F][-I][-r][-R][-D][-M][-Y][-RD][-RM][-RY][-h]\n[--for-full-backup][-F][-folder-names]\n[--for-incremental-backup][-I][-folder-names]\n[--for-file-restore][-r][-file-names]\n[--for-folder-restore][-R][-folder-names]\n[--for-restore-files-beforeDate][-D][-number-before-backup]\n[--for-restore-files-beforeMonths][-M][-number-of-months]\n[--for-restore-files-beforeyear][-Y][-number-before-backup]\n[--for-remove-files-beforeDates][-RD][-number-before-date]\n[--for-remove-files-beforeMonths][-RM][-number-before-months]\n[--for-remove-files-beforeyear][-RY][-number-before-year]\n[-h][--for-Details]\n\n");
		}
	}
	sqlite3_close(db);
	WriteLogForlibmwshare(4,"Help ended" );
}



