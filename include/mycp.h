#ifndef MYCP__H

#define MYCP__H

#define SIZE 1024
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>




char inputFile[50];
char outputFile[50];
				
char inbuf[1024];
char outbuf[1024];
				

char intemp[1024];							
char outtemp[1024];
			
void CopyFile(char* inputFile, char* outputFile);
int folderCopy(DIR* inputdir,DIR* outputdir);

#endif
