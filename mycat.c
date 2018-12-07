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
#define SZ_BUF 1024
int main(int argc, char * argv[])
{
	int fd_in,fr;
	struct stat sbuf;
	DIR *dirp;
	struct dirent *dp;
	char buf[SZ_BUF];
	mode_t file_mode;
	int num=0;
	if(argc ==1)
 	{
 		fprintf(stderr,"usage mycat dirname\n");
 		exit(0);
 	}
 	// file check 
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
                   if(S_ISDIR(file_mode))
 		  {
 			num=2;
 			break;
 		  }
 	}
 	if(num==1)
		printf("There is no file in here!\n");
	else if(num==2)
		printf("Directory name!\n");
	//open file and write terminal
	for(int i=1;i<argc;i++)
	{
		FILE * fd=fopen(argv[i],"rt");
		while(fgets(buf,SZ_BUF,fd)!=NULL)
			printf("%s",buf);
	}
			
}
