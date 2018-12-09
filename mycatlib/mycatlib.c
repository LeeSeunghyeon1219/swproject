#include <fcntl.h>
#include <sys/types.h>
#include<sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include <grp.h>
#include "mycat.h"
#define SZ_BUF 1024

void mycat(int argc, char *argv[])
{
        int fd_in,fr;
        struct stat sbuf;
        DIR *dirp;
        struct dirent *dp;
        char buf[SZ_BUF];
        mode_t file_mode;
        int num=0;

        dirp=opendir(".");
        for(int i=1;i<argc;i++)
        {
                  int s=stat(argv[i],&sbuf);
                  if(s==-1)
                  {
                        num=1;
                        break;
                  }
                   file_mode=sbuf.st_mode;
                   if(!S_ISREG(file_mode))
                  {
                        num=2;
                        break;
                  }
        }
        if(num==1)
        {
                printf("There is no file in here!\n");
                return;
        }
        else if(num==2)
        {
	        printf("Directory name!\n");
		return;	
	}        
	//open file and write terminal
        for(int i=1;i<argc;i++)
        {
                FILE * fd=fopen(argv[i],"rt");
                while(fgets(buf,SZ_BUF,fd)!=NULL)
                        printf("%s",buf);
        }
	return;
}
