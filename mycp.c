#define SIZE 1024

#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>


void CopyFile(char* inputFile, char* outputFile){

//파일 복사하기
	printf("파일 복사\n");

	struct stat frstatbuf;
	FILE* fr=fopen(inputFile,"r");
	
	if(fr==NULL){
		perror("read file 읽기 오류\n");
		exit(0);
	}

	int frfd=fileno(fr);

	fstat(frfd,&frstatbuf);


	FILE* fw=fopen(outputFile,"w+");

	
	if(fw==NULL){
		perror("write file 열기 오류\n");
		exit(0);
	}
	

	int fwfd=fileno(fw);

	fchmod(fwfd,frstatbuf.st_mode);
	
	
	char buf[1024];

	while(1){
		int n=fread(buf,sizeof(char),SIZE,fr);

		if(n<SIZE){
			fwrite(buf,sizeof(char),n,fw);
			printf("파일을 다 읽었음\n");
			exit(0);
		}

		fwrite(buf,sizeof(char),n,fw);
	}
	
	 fclose(fr);
	 fclose(fw);



}


int main(int argc, char *argv[]){

	if(argc<3){
		perror("argument 부족\n");
		exit(0);
	}
	
	if(argc==3){
		CopyFile(argv[1],argv[2]); 
	}

	if(argc==4){
		if(strcmp(argv[1],"-r")==0){
			printf("폴더복사\n");
			
			DIR* inputdir;
			inputdir=opendir(argv[2]); //폴더를 연다


			//폴더를 읽는다 
			
			while(1){

			struct dirent * rddir=readdir(inputdir);
		
			if(rddir==NULL){
				//directory stream 끝에 도달하거나 에러 발생하면 0
				exit(0);
			}


			
			//stat을 통해 파일 종류 확인하기 
			struct stat buf;
			stat(rddir->d_name,&buf);
			
			int flag=0;

			//파일인지 폴더인지 확인
			switch (buf.st_mode & S_IFMT){
			 case S_IFBLK:  printf("block device\n");            						flag=0; break;
          		 case S_IFCHR:  printf("character device\n");        						flag=1; break;
           		 case S_IFDIR:  printf("directory: ");
printf("%s\n",rddir->d_name);	
					printf("----------------\n");
				
					flag=2; break;
           		 case S_IFIFO:  printf("FIFO/pipe\n");               						flag=3; break;
           		 case S_IFLNK:  printf("symlink\n");                 						flag=4; break;
           		 case S_IFREG:  printf("regular file : ");  
					printf("%s\n",rddir->d_name);
					printf("-----------------\n");
          				flag=5; break;
 		         case S_IFSOCK: printf("socket\n");                  						flag=6; break;
           		 default:       printf("unknown?\n");                						flag=7; break;


			}
			//입력 폴더를 복제할 출력 폴더를 만든다.
		 	
			mkdir(argv[3],777); //폴더 만들
			chmod(argv[3],buf.st_mode); //폴더 권한을 똑같이 설정

			//정상적으로 입력 폴더를 읽었으면 폴더 속 파일이름  출력
			if(flag==2){
			//폴더이므로 폴더를 만든다. 이 폴더 안의 파일도 확인한다.
			//재귀함수 
			}
			
			if(flag==5){
			//파일이므로 파일을 복사한다.
			printf("%s\n",rddir->d_name);
			
			char* outputFile=strcat(argv[3],"\\");
			outputFile=strcat(outputFile,rddir->d_name);

			CopyFile(rddir->d_name,outputFile);
			}
		}
		}
		}

	return 0;

}
	
