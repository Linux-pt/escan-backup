#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string.h>
#include<iostream>
#include<fstream>
#include<sqlite3.h>
#include"unzip.h"
#include"Extract.h"
#include<vector>
using namespace std;

int UnzipFile(char *ZipName,const char *ZipItem)
{
	HZIP hz = OpenZip(ZipName , 0);
	SetUnzipBaseDir(hz, "/tmp");
	ZIPENTRY ze;
	GetZipItem(hz, -1, &ze);
	int numitems=ze.index;
	for (int zi=0; zi<numitems; zi++)
	{
		GetZipItem(hz, zi, &ze);
		UnzipItem(hz, zi, ze.name);
		if( strlen( ze.name ) != 0 )
		{
			if(strcasecmp(ZipItem,ze.name)==0)
			{		
				UnzipItem(hz, zi, ze.name);
	CloseZip(hz);
	return 0;
				
				break;
			}
			//printf("File Name='%s'\n",ze.name);
			//listOfFileName.push_back(ze.name);
			//listOfPolicies.push_back( ze.name );
		}
	}
	CloseZip(hz);
	return -1;


}

int ifpresent1BinaryEx(char *bufferParam, char *srchstr, int bufferlen)
{
	int j = 0;

	//__try
	//{
		int excludestlen;
		unsigned char *buffer = (unsigned char*)bufferParam;

		if (bufferParam == NULL || srchstr == NULL)
			return(-1);

		excludestlen = strlen(srchstr);
		if (bufferlen < excludestlen)
			return(-1);

		//char c = my_toupper(srchstr[0]);
		char c = toupper(srchstr[0]);
		for (j = 0; j <= (bufferlen - excludestlen); j++)
		{
			//if (c == my_toupper(buffer[j]))
			if (c == toupper(buffer[j]))
			{
				if (strncasecmp(srchstr, (char*)&buffer[j], excludestlen) == 0)
					return(j);
			}
		}
	//}

	//__except (EXCEPTION_EXECUTE_HANDLER)
//	{
//	}

	return(-1);
}



int ExtractZip(char *ZipName, char *DestinationFolderName ,int *vulnerable,int *Patched)
{

	vector<string> listOfFileName;
	HZIP hz = OpenZip(ZipName , 0);
	SetUnzipBaseDir(hz, DestinationFolderName);
	ZIPENTRY ze;
	GetZipItem(hz, -1, &ze);
	int numitems=ze.index;
	for (int zi=0; zi<numitems; zi++)
	{
		GetZipItem(hz, zi, &ze);
		UnzipItem(hz, zi, ze.name);
		if( strlen( ze.name ) != 0 )
		{
			//printf("File Name='%s'\n",ze.name);
			listOfFileName.push_back(ze.name);
			//listOfPolicies.push_back( ze.name );
		}
	}
	CloseZip(hz);
			//free(buff);
	return 0;
				//free(buff);
}


