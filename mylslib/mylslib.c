#include "myls.h"
struct node{
	char *name;
	struct node *next;
};
void addToSLL(char *_name)
 {
         struct node * temp = (struct node *)malloc(sizeof(struct node*));
 	temp->name =(char *)malloc(sizeof(char)*(strlen(_name)+1));
 	strcpy(temp->name,_name);
 	temp->next=0;
 
 	if(head==0)
 	{
 		head=temp;
 		return;
 	}
 	else
 	{
 		struct node *cur=head;
 		while(cur->next!=0)
 			cur=cur->next;
 		cur->next=temp;
 	}
 	return;
 }
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
 void showSLL()
 {
 	struct node *temp=head;
 	while(temp!=0)
 	{
 		printf("%s  ",temp->name);
 		temp=temp->next;
 	}
 }
 void showSLL_list()
 {
 	struct stat sbuf;
         struct node *temp=head;
         while(temp!=0)
         {
                  mode_t file_mode;
                  struct tm *tminfo;
                  char buf1[80];
                  stat(temp->name,&sbuf);
                  file_mode=sbuf.st_mode;
                  rwx(file_mode);
                  printf("%2d ",(int)sbuf.st_nlink);
                  printf("%s ",getpwuid(sbuf.st_uid)->pw_name);
                  printf("%s ",getgrgid(sbuf.st_gid)->gr_name);
                  printf("%5d ",(int)sbuf.st_size);
                  tminfo=localtime((&sbuf.st_atime));
                  strftime(buf1,80,"%m/%d %H:%M",tminfo);
                  printf("%s ",buf1);
 		 printf("%s\n",temp->name);
       		 temp=temp->next;
 	  }
 }
 void sortSLL()
 {
 	struct node *temp=head;
 	struct node *cur=temp->next;
 	char c[100]="";
 	while(temp->next!=0)
 	{
 		if(strcmp(temp->name,cur->name)>0)
 		{
 			strcpy(c,temp->name);
 			strcpy(temp->name,cur->name);
 			strcpy(cur->name,c);			
 		}
 		cur=cur->next;
 		if(cur==0)
 		{
 			temp=temp->next;
 			cur=temp->next;
 		}
 	}
 }
 void opendirp(DIR *dirp)
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
                                 if(dp->d_name[0]=='.')
                         	        continue;
 				addToSLL(dp->d_name);
                         }
                 }
         }
 }
 void opendirp_all(DIR * dirp)
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
                                 addToSLL(dp->d_name);
                }
	}
}
