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

int main(int argc, char * argv[])
{
	int num=0;
	struct stat sbuf;
	DIR *dirp;
	struct dirent *dp;

	if(argc !=1)
	{
		fprintf(stderr,"usage mycat dirname\n");
		exit(0);
	}
	else if(argc==2)
	{
		dirp=opendir(argv[1]);
	}
	if(dirp==NULL)
	{
		perror("opendir");
		exit(0);
	}
	else
		printf("clear!\n");
}
