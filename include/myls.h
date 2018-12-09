#ifndef MYLS__H
#define MYLS__H

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include <grp.h>

void addToSLL(char *_name);
void rwx(mode_t filemode);
void sortSLL();
void showSLL();
void showSLL_list();
void opendirp_all(DIR * dirp);
void opendirp_all(DIR * dirp);

#endif
