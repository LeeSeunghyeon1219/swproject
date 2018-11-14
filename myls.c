#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
			printf("%s	",dp->d_name);	
			stat(dp->d_name, &sbuf);
			if(S_ISREG(sbuf.st_mode))
			{
				printf("regular file\n");
			}
			else if(S_ISDIR(sbuf.st_mode))
			{
				printf("Directory\n");
			}
			else
			{
				printf("Other\n");
			}
		}
	}
	
		
}
