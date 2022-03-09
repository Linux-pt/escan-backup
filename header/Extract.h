#ifndef __Extract_H_
#define __Extract_H_
int UnzipFile(char *ZipName,const char *ZipItem);
int ifpresent1BinaryEx(char *bufferParam, char *srchstr, int bufferlen);
int ExtractZip(char *ZipName, char *DestinationFolderName ,int *vulnerable,int *Patched);
#endif
