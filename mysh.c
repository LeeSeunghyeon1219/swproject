#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include<sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <unistd.h>
#include <grp.h>
#define SZ_BUF 1024
#define STR_LEN 256
#define NUM_OF_TOKENS 10
int mycat(int argc, char * argv[])
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
int main(void)
{
	char cmdString[STR_LEN];
	char *cmdTokenList[NUM_OF_TOKENS];
	char delim[]=" ";
	char *token;
	int tokenNum;
	int exitCode=0;
	printf("write your command!\n");
	char SZ[1024]="";
	int argc=0;
	while(1)
	{
		fgets(cmdString,STR_LEN,stdin);
		tokenNum++;
		token=strtok(cmdString,delim);
		while(token)
		{
			cmdTokenList[tokenNum]=malloc(sizeof(char)*strlen(token)+1);	
			strcpy(cmdTokenList[tokenNum],token);
			token=strtok(NULL,delim);
			
			printf("%d : %s\n",tokenNum,cmdTokenList[tokenNum]);
			tokenNum++;
		}
		
	 	if(strcmp(cmdTokenList[0],"cat")==0)
			mycat(tokenNum,cmdTokenList);	
		tokenNum=0;	
	}	
}

