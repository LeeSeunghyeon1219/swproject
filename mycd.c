#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include <string.h>
#include <dirent.h>
int main(int argc, char *argv[])
{
	int num=0;
	struct stat sbuf;
	DIR *dirp;
	struct dirent  *dp;

	if(argc!=2)
	{
		fprintf(stderr, "useage mycd dirname\n");
		exit(0);
	}
	else
	{
		stat(argv[1],&sbuf);
	}
}
