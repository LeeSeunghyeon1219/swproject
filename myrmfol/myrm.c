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
#include "myrm.h"
#define SZ_BUF 1024

int main(int argc, char *argv[])
{
	int num=0;
	if(argc==1)
	{
		fprintf(stderr,"usage myrm dirname\n");
		exit(0);
	}
	else
	{
		if(strcmp(argv[1],"*")==0)
			all_rm(argc,argv);
		else if(strcmp(argv[1],"-r")==0)
			return dir_rm(argv[2],1);
		else
			file_rm(argc,argv);
	}
	return 0;
}
