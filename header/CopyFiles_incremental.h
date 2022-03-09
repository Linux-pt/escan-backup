#ifndef __CopyFiles_incremental_H_
#define __CopyFiles_incremental_H_
void CopyFiles_incremental(char *);
static int remove_folder(const char *pathname, const struct stat *sbuf, int type, struct FTW *ftwb);
#endif
