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
int main(int argc, char * argv[])
{
	int fd_in,fr;
	struct stat sbuf;
	DIR *dirp;
	struct dirent *dp;
	char buf[SZ_BUF];
	mode_t file_mode;
	int num=0;
	if(argc==1)
	{
		fprintf(stderr,"usage mycat dirname\n");
 		exit(0);
 	}
	else
		mycat(argc, argv);
}
