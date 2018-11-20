#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char *argv[])
{
	struct stat sbuf;
	DIR *dirp;
	struct dirent *dp;
	if (argc != 2)
	{
		fprintf(stderr,"usage myls dirname\n");
		exit(0);
	}
	
	dirp=opendir(argv[1]);
	if(dirp==NULL)
	{
		perror("opendir");
		exit(0);
	}
	for(;;)
	{
		dp=readdir(dirp);
		if(dp==NULL)
		{
			break;
		}
		else
		{
			if(strcmp(dp->d_name,".")==0)
				continue;
			if(strcmp(dp->d_name,"..")==0)
				continue;
			if(strcmp(dp->d_name,".git")==0)
				continue;
			printf("%s\n",dp->d_name);	
			stat(dp->d_name, &sbuf);
	//		if(S_ISREG(sbuf.st_mode))
	//		{
	//			printf("regular file\n");
	//		}
	//		else if(S_ISDIR(sbuf.st_mode))
	//		{
	//			printf("Directory\n");
	//		}
	//		else
	//		{
	//			printf("Other\n");
	//		}
		}
	}
	
		
}
