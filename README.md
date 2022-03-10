# escan-backup

<<------------ESCAN-BACKUP----------->>

1.Requirement-->>>>SQLITE3,C,C++,libzip(library),pthread

2.Development-->1.Full-backup
2.Incremental-backup
3.Restore data
4.Remove data


3.Brief-->

	1.Full-Backup-->1.A full backup is the process of creating copies of all organizational data files in a single backup operation.

	2.Incremental Backup-->a security copy which contains only those files which have been altered since the last full backup.

	3.Restore data-->this will restore the files as per CLI and flags

	4.Remove data-->this will remove the files as per CLI and flags

	5.Info--->> this will print all the flags for escan-backup	

4.Algorithm-->

	1.firsly we maintain database on /tmpdata/escanAV/{backup/escanIncremental/Restore/.backup.db} like folder structure where we are storing copies of data and maintaining database and we are maintaing 3 tables in it backup,tmpdata,path...In which in backup we are storing fullbackup details and in tmpdata table we are storing /tmpdata/escanAV/backup folder detailsand in path we are storing which path has been full backup has been done.

	2.we are firstly doing (full-backup)-->and we are making copy of that folder into /tmpdata/escanAV/Backup folder in which we are .backup.db file was made in which all the tables are maintain for that folder structure.

	3.for Incremental backup we comparing files on the basis of sha1sum and we can make incremental backup.on the basis of this we are making archieve copy of previous stat of that file and maintaining recent updated files and that details into .backup.db file.major factor in incremental backup was firstly we compare filename and sha1sum and path if name and path was same but sha1sum was diffrent then we archieve that file.and we are modify that file in backup directory.

	4.Restore the files we just normally copying the files and with the help of libzip we are extracting files and folder.

	5.Remove the files-->if we dont want to store the files then we can remove that files also.


5.COMMANDS_USED_IN_IT----->>>

	1.cp-->copy.
	2.sha1sum-->to find the uniq indentity of files.


6.Flags which we made----->




	[escan-backup][-F][-FOLDER-NAME][--FOR-FULL-BACKUP]
	[escan-backup][-I][-FOLDER-NAME][--FOR-INCREMENTAL-BACKUP]
	[escan-backup][-r][-FILE-NAME-AS-PER-TMPDATA][--FOR-FILE-RESTORE]
	[escan-backup][-d][-FILE-NAME-AS-PER-TMPDATA][--FOR-FILE-REMOVE]
	[escan-backup][-R][-FOLDER-NAME][--FOR-FOLDER-RESTORE]
	[escan-backup][-RBD][-BEFORE-DATE-COUNT][--FOR-RESTORE-FILES-BEFORE-DATE]
	[escan-backup][-RBM][-BEFORE-MONTH-COUNT][--FOR-RESTORE-FILES-BEFORE-MONTH]
	[escan-backup][-RBY][-BEFORE-YEAR-COUNT][--FOR-RESTORE-FILES-BEFORE-YEAR]
	[escan-backup][-DBD][-BEFORE-DATE-COUNT][--FOR-REMOVE-FILES-BEFORE-DATE]
	[escan-backup][-DBM][-BEFORE-MONTH-COUNT][--FOR-REMOVE-FILES-BEFORE-DATE]
	[escan-backup][-DBY][-BEFORE-YEAR-COUNT][--FOR-REMOVE-FILES-BEFORE-YEAR]
	[escan-backup][-RAD][-AFTER-DATE-COUNT][--FOR-RESTORE-FILES-AFTER-DATE]
	[escan-backup][-RAM][-AFTER-MONTH-COUNT][--FOR-RESTORE-FILES-AFTER-MONTH]
	[escan-backup][-RAY][-AFTER-YEAR-COUNT][--FOR-RESTORE-FILES-AFTER-YEAR]
	[escan-backup][-DAD][-AFTER-DATE-COUNT][--FOR-REMOVE-FILES-AFTER-DATE]
	[escan-backup][-DAM][-AFTER-MONTH-COUNT][--FOR-REMOVE-FILES-AFTER-DATE]
	[escan-backup][-DAY][-AFTER-YEAR-COUNT][--FOR-REMOVE-FILES-AFTER-YEAR]
	[[escan-backup]-INFO][-READ-DATA-FROM-TMPDATA][-READ-DATA-FROM-BACKUP]
	[escan-backup][-H][-HELP]

7.Flow------>>>

	[FULL-BACKUP]--{CP COMMAND}--[DATA-BASE-MAINTAIN]
	[INCREMENTAL-BACKUP]----{ON THE BASIS OF COMPARISON BETWEEN SHA1SUM BETWEEN FILES WE ARE ARCHIEVEVING FILES}----[NEW DATA MAINTAIN IN BACKUP FOLDER]
	[RESTORE]---{FILE NAME OR FOLDER NAME}-----[FILES RESTORE IN RESTORE FOLDER]
	[REMOVE]--{FILES}---[FILES REMOCE BEFORE AFTER DATE MONTH AND YEAR]



8.example----->>

	1. ./escan-backup -F {directory-name}
	2. ./escan-backup -I {directory-name-which-is-having-full-backup}
	3. ./escan-backup -R {folder-name}
	4. ./escan-backup -r {file restore}
	5. ./escan-backup {RBD} {count-before-restore}
	6. ./escan-backup {RBM} {count-before-restore}
	7. ./escan-backup {RBY} {count-before-restore}
	8. ./escan-backup {RAD} {count-after-restore}
	9. ./escan-backup {RAM} {count-after-restore}
	10. ./escan-backup {RAY} {count-after-restore}
	11. ./escan-backup {DBD} {count-before-delete}
	12. ./escan-backup {DBM} {count-before-delete}
	13. ./escan-backup {DBY} {count-before-delete}
	14. ./escan-backup {DAD} {count-after-delete}
	15. ./escan-backup {DAM} {count-after-delete}
	16. ./escan-backup {DAY} {count-after-delete}
	17. ./escan-backup -INFO
	118. ./escan-backup -HELP

9.Diagram---->>


	[DATA]------[MAKING A COPY]----[/tmpdata/escanAV/{backup/escanIncremental/restore/.backup}]
	[INCREMENTAL-BACKUP]---[IF--(CHANGES)--->>>>ARCHIEVE THE FILES]----ELSE---[DO NOTHING]



	[FULL-BACKUP]---->
		[CREATING-FOLDER]---->[FOLDER PRESENT]----->[DONT DO ANYTHING]
				----[FOLDER NOT PRESENT]--->[CREATE FOLDER]

		[DATABSE]---{PRESENT}--------{DONT CREATE}
			-{NOT PRESENT}----{CREATE}

		[CHECKING BACKUP]----{IF BACKUP PRESENT}------{DONT DO}
				----{IF BACKUP NOT PRESENT}---{DO BACKUP}

		[STORAGE]---[FILE STORAGE IS GREATER THAN APPROXIMATELY 1GB OF AVAILABLE STORAGE]----[DO FULL-BACKUP]
			----[FILE STORAGE IS LESS THAN APPROXIMATELY 1GB OF AVAILABLE STORAGE]-------[DONT DO FULL BACKUP]--[SPACE NOT AVAILABLE]
			----[CALCULATING ABSOLUTE PATH]-----[CHECKING WHETHER IT IS PRESENT IN DATABSE IF BACKUP IS DONT OR NOT]--[IF NOT THEN DO FB]
			----[INSERTING DATA IN DATABASE(TMPDATA,BACKUP,PATH) AND COPYING FILES]
			----[DATABSE CLOSE]

	[INCREMENTAL-BACKUP]---->
		[DATABASE]----{PRESENT}---{DO INCREMENTAL BACKUP}
			{NOT PRESENT}-----{FIRST DO INCREMENTAL BACKUP}

	[STORAGE]---->[FILE STORAGE IS GREATER THAN APPROXIMATELY 1GB OF AAILABLE STORAGE]----[DO INCREMENTAL-BACKUP]
		----[FILE STORAGE IS LESS THAN APPROXIMATELY 1GB OF AVAILABLE STORAGE]--[DONT DO INCREMENTAL BACKUP]---[SPACE NOT AVAILABLE]
		----[CALCULATING ABSOLUTE PATH]---[COMPARING FILES DETAILS(SHA1SUM,FILENAME,FILE_PATH)]---[ON THAT BASIS WE ARE ARCHIEVEING]
		----[AFTER COMPARING WE HAVE TO COPY THE FILES]
		----[MODIFICATION IN DATABASE]

	[RESTORE-FILES]---->
		[FILE-RESTORE]--->[ON THE BASIS OF NAME WE ARE EXTRACTING THE FILES]


	[RESTORE-FOLDER]---->
		[FOLDER-RESTORE]---->[COPY THE FOLDER SAME AS THAT]


	[{DELETE/RESTORE}--FILES-ON-THE-BASIS-DATE]---->
	[DELETE/RESTORE-FILES]---->[RESTORE/REMOVE]---[FILES]

10.LIBRARIES-------->>>>
	
	linux-vdso.so.1 =>  (0x00007fff32fd6000)
	libzip.so => /usr/lib/libzip.so (0x00007fca06890000)
	libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007fca06671000)
	libsqlite3.so.0 => /usr/lib/x86_64-linux-gnu/libsqlite3.so.0 (0x00007fca06369000)
	libstdc++.so.6 => /usr/lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007fca05fe3000)
	libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007fca05dcc000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fca059ec000)
	/lib64/ld-linux-x86-64.so.2 (0x00007fca06cc6000)
	libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007fca05696000)
	libdl.so.2 => /lib/x86_64-linux-gnu/libdl.so.2 (0x00007fca05492000)


11.MODIFICATIONS------->>>>>>
