#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include<pwd.h>
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
void base(DIR *dirp)
{
        struct stat sbuf;
        struct dirent *dp;
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
void a_option(DIR * dirp)
{
        struct stat sbuf;
        struct dirent *dp;
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
void al_option(DIR *dirp)
{
        struct stat sbuf;
        struct dirent *dp;
        
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
                                mode_t file_mode;
                                struct tm *tminfo;
                                struct passwd *my_passwd;
                                struct group *my_group;
                                char buf1[80];
                                stat(dp->d_name,&sbuf);
                                file_mode=sbuf.st_mode;
                                rwx(file_mode);
                                printf("%2d ",(int)sbuf.st_nlink);
                                printf("%s ",getpwuid(sbuf.st_uid)->pw_name);
                                printf("%s ",getgrgid(sbuf.st_gid)->gr_name);
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
void l_option(DIR *dirp)
{
        struct stat sbuf;
        struct dirent *dp;

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
                                printf("%2d ",(int)sbuf.st_nlink);
                                printf("%s ",getpwuid(sbuf.st_uid)->pw_name);
                                printf("%s ",getgrgid(sbuf.st_gid)->gr_name);
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
		else if(strcmp(argv[1],"-al")==0|strcmp(argv[1],"-all")==0)
			num=3;
 	}
 	else
  		dirp=opendir(".");


 	if(num==0)//base
		base(dirp);
 	else if(num==1)//-a --all
 		a_option(dirp);	
	else if(num==2)//-l
		l_option(dirp);		
	else if(num==3)
		al_option(dirp);	
} 


