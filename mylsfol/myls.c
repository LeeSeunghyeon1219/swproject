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
#define SZ_BUF 1024

#include "myls.h"
struct node *head=0;
int main(int argc, char *argv)
{
	int num=0;
 	struct stat sbuf;
 	DIR *dirp;
 	struct dirent *dp;
 
 	 //compare argc
 	if (argc != 1 & argc!=2 & argc !=3)
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
	else if(argc==3)
	{
                if(strcmp(argv[1],"..")==0|strcmp(argv[2],"..")==0)
                        dirp=opendir("..");
		else
			dirp=opendir(".");
		
		if((strcmp(argv[1],"-a")==0&strcmp(argv[2],"-l")==0)|(strcmp(argv[2],"-a")==0&strcmp(argv[1],"-l")==0))
			num=3;
                else if(strcmp(argv[1],"-a")==0|strcmp(argv[1],"--all")==0|strcmp(argv[2],"-a")==0|strcmp(argv[2],"--all")==0)
                        num=1;
                else if(strcmp(argv[1],"-l")==0|strcmp(argv[2],"-l")==0)
                        num=2;
                else if(strcmp(argv[1],"-al")==0|strcmp(argv[1],"-all")==0|strcmp(argv[2],"-al")==0|strcmp(argv[2],"-all")==0)
                        num=3;

	}
  	else
   		dirp=opendir(".");
 
 
  	if(num==0)//base
 	{
                opendirp(dirp);
                sortSLL();
                showSLL();
		printf("\n");
  	}
	else if(num==1)//-a --all
	{
                opendirp_all(dirp);
                sortSLL();
                showSLL();
                printf("\n");
	} 
	else if(num==2)
        {
                opendirp(dirp);
                sortSLL();
                showSLL_list();
        }
 	else if(num==3)
	{
 		opendirp_all(dirp);
	        sortSLL();
        	showSLL_list();
	}	
	
} 
