#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <grp.h>
void rwx(mode_t filemode)
{
	if(S_ISDIR(filemode))
		printf("d");
	else
		printf("-");
	
	if(filemode & S_IRUSR)
		printf("r");
	else
		printf("-");
		
	if(filemode & S_IWUSR)
		printf("w");
	else
		printf("-");

	if(filemode & S_IXUSR)
		printf("x");
	else
		printf("-");
	
	if(filemode & S_IRGRP)
		printf("r");
	else
		printf("-");

	if(filemode & S_IWGRP)
		printf("w");
	else
		printf("-");

	if(filemode & S_IXGRP)
		printf("x");
	else
		printf("-");

	if(filemode & S_IROTH)
		printf("r");
	else
		printf("-");

	if(filemode & S_IWOTH)
		printf("w");
	else
		printf("-");

	if(filemode & S_IXOTH)
		printf("x");
	else
		printf("-");
	printf(" ");
}
int main(int argc, char *argv[])
{
	int num=0;
	struct stat sbuf;
	DIR *dirp;
	struct dirent *dp;

	 //compare argc
	if (argc != 1 & argc!=2)
	{
		fprintf(stderr,"usage myls dirname\n");
		exit(0);
	}
	else if(argc ==2)
	{
		if(strcmp(argv[1],"..")==0)
			dirp=opendir("..");
 		else
			dirp=opendir(".");

  		if(strcmp(argv[1],"-a")==0|strcmp(argv[1],"--all")==0)
   			num=1;
		else if(strcmp(argv[1],"-l")==0)
			num=2;
 	}
 	else
  		dirp=opendir(".");


 	if(num==0)//base
 	{
  		if(dirp==NULL)
  		{
   			perror("opendir");
   			exit(0);
  		}
  		else
  		{
   			for(;;)
   			{
    				dp=readdir(dirp);
    				if(dp==NULL)
     					break;
    				else
    				{
     					if(strcmp(dp->d_name,".")==0)
      						continue;
     					if(strcmp(dp->d_name,"..")==0)
       						continue;
     					if(strcmp(dp->d_name,".git")==0)
      						continue;
     					if(strcmp(dp->d_name,".gitignore")==0)
      						continue;
     					printf("%s  ",dp->d_name);	
     					stat(dp->d_name, &sbuf);
    				}
   			}
   			printf("\n");  
  		}
 	}
 	else if(num==1)//-a --all
 	{
  		if(dirp==NULL)
  		{
   			perror("opendir");
   			exit(0);
 		 }
  		else
  		{
   			for(;;)
   			{
    				dp=readdir(dirp);
    				if(dp==NULL)
     					break;
    				else
    				{
     					printf("%s  ",dp->d_name);
     					stat(dp->d_name, &sbuf);
    				}
   			}
  		}
  		printf("\n");
 	}
	else //-l
	{
		
		if(dirp==NULL)
		{
			perror("opendir");
			exit(0);
		}
		else
		{
			for(;;)
			{
				dp=readdir(dirp);
				if(dp==NULL)
					break;
				else
				{
                                        if(strcmp(dp->d_name,".")==0)
                                                continue;
                                        if(strcmp(dp->d_name,"..")==0)
                                                continue;
					if(strcmp(dp->d_name,".git")==0)
                                                continue;
                                        if(strcmp(dp->d_name,".gitignore")==0)
                                                continue;

					mode_t file_mode;
					struct tm *tminfo;
					struct passwd *my_passwd;
					struct group *my_group;
					char buf1[80];
					stat(dp->d_name,&sbuf);
					file_mode=sbuf.st_mode;
					rwx(file_mode);
					printf("%d ",(int)sbuf.st_nlink);
			//		my_passwd=getpwuid(sbuf.st_uid);
			//		my_group=getgrgid(sbuf.st_gid);
				//	printf("%s ",sbuf.st_uid);
				//	printf("%s ",sbuf.st_gid);
					printf("%5d ",(int)sbuf.st_size);
					tminfo=localtime((&sbuf.st_atime));
					strftime(buf1,80,"%m/%d %H:%M",tminfo);
					printf("%s ",buf1);
					
					if(dp->d_name !=0)
						printf("%s\n",dp->d_name);
					
				}
			}
						
		}
	}
} 


