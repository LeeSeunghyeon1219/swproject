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
int main(int argc, char * argv[])
{
	int fd_in;
	struct stat sbuf;
	DIR *dirp;
	struct dirent *dp;
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
	else//right;
	{
	}		
}
