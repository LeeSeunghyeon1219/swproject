#include "myrm.h"
void all_rm(int argc, char *agrv[])
{
	struct stat sbuf;
        DIR *dirp;
        struct dirent *dp;
        char buf[SZ_BUF];
        mode_t file_mode;
        int num=0;

        dirp=opendir(".");
        //remove file
        for(int i=1;i<argc;i++)
        {
                dp=readdir(dirp);
		if(dp==NULL)
			break;
		else
		{
        	       	stat(argv[i],&sbuf);
		     	file_mode=sbuf.st_mode;
	          	if(!S_ISREG(file_mode))
                      		continue;
			if(strcmp(dp->d_name,"myrm")==0)
				continue;
			if(dp->d_name[0]=='.')
				continue;
			unlink(dp->d_name);
		}
        }
}
int dir_rm(char *path, int is_error_stop)
{
	DIR *dir_ptr=NULL;
	struct dirent *file=NULL;
	struct stat buf;
	char filename[1024]="";

	if((dir_ptr=opendir(path))==NULL)
	{
			return unlink(path);
	}
	while((file=readdir(dir_ptr))!=NULL)
	{
                if(file->d_name[0]=='.')
                        continue;
		sprintf(filename,"%s/%s",path,file->d_name);
		if(lstat(filename,&buf)==-1)
			continue;
		if(S_ISDIR(buf.st_mode))
		{
			if(dir_rm(filename,is_error_stop)==-1&&is_error_stop)
				return -1;
		}
		else if(S_ISREG(buf.st_mode)||S_ISLNK(buf.st_mode))
		{
			if(unlink(filename)==-1&&is_error_stop)
				return -1;
		}	
	}
	closedir(dir_ptr);
	return rmdir(path);
}
void file_rm(int argc, char * argv[])
{
        int fd_in,fr;
        struct stat sbuf;
        DIR *dirp;
        struct dirent *dp;
        char buf[SZ_BUF];
        mode_t file_mode;
        int num=0;
	int ch=0;
        dirp=opendir(".");
        for(int i=1;i<argc;i++)
        {
                if(argv[i][0]=='*')
		{
			ch=1; 
			continue; 
		}
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
        {
                printf("There is no file in here!\n");
                return;
        }
        else if(num==2)
        {
                printf("Directory name!\n");
                return;
        }
        //remove file
        for(int i=1;i<argc;i++)
	{
                if(strcmp(argv[i],"*")==0)
			continue; 
		unlink(argv[i]);
	}
	if(ch==1)
	{
		for(int i=1;i<argc;i++)
		{
		        dirp=opendir(".");
			char *ptr;
                	if(argv[i][0]!='*')
                		continue;
			else
			{
				ptr=strtok(argv[1],".");
				ptr=strtok(NULL," ");
				for(;;)
				{
					dp=readdir(dirp);
					if(dp==NULL)
						break;
					else
					{
						char *ptr1=strtok(dp->d_name,".");
						ptr1=strtok(NULL," ");
						if(strcmp(ptr1,ptr)==0)
							unlink(dp->d_name);
					}
				}
			}
			
		}
	}
        return;
}
