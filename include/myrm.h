#ifndef MYRM__H
#define MYRH__H

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

void all_rm(int argc, char *agrv[]);
void dir_rm(int argc, char *argv[]);
void file_rm(int argc, char *argv[]);

#endif

