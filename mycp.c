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
#include <errno.h>

void CopyFile(char* inputFile, char* outputFile){

//파일 복사하기
	printf("파일 복사\n");
	printf("inputFile: %s, outputFile: %s \n",inputFile,outputFile);
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
			inputdir=opendir(argv[2]); //input 폴더를 연다
	
			//input폴더를 읽는다 
			
			//input 폴더를 복제할 output 폴더를 만든다.
		 	struct stat buf;
			stat(argv[2],&buf);
			int mkdirFlag=mkdir(argv[3],buf.st_mode); 



			if(mkdirFlag==0){
				printf("output 폴더 만들기 성공하였습니다.\n");
				
			}

			else{
				perror("폴더를 만들지 못하였습니다.\n");
				printf("%d: %s\n",errno,strerror(errno));
				
				exit(0);
				}


				DIR* outputdir;
				outputdir=opendir(argv[3]);

			while(1){

			struct dirent * rddir=readdir(inputdir);
			struct dirent * outrddir=readdir(outputdir);
		
			if(rddir==NULL){
				//directory stream 끝에 도달하거나 에러 발생하면 0
				exit(0);
			}


			//파일인지 폴더인지 확인
		
			if(rddir->d_type == DT_DIR){
				//폴더이다.
				printf("폴더입니다\n");
			//input 폴더를 복제할 output 폴더를 만든다.
		 			struct stat buf;
					stat(rddir->d_name,&buf);
				int mkdirFlag=mkdir(rddir->d_name,buf.st_mode); 
				
			
				if(mkdirFlag==0){
					printf("output 폴더 만들기 성공하였습니다.\n");
					}

				else{
					perror("폴더를 만들지 못하였습니다.\n");
					printf("%d: %s\n",errno,strerror(errno));
				
					exit(0);
					}


				//폴더 복사를 위해서 재귀함수를 호출한다.

				}
		else if(rddir->d_type==DT_REG){
				//regular file이면 파일복사를 한다.

				//파일 이름을 출력한다.
				printf("파일 입니다 : %s\n",rddir->d_name);
			
				//input 폴더의 경로를 설정해준다.
			
				//char* inputFile=(rddir->d_name);
		
				char inputFile[50];
				inputFile[0]='\0';

				strcat(inputFile,"./");
				
				strcat(inputFile,argv[2]);
				strcat(inputFile,"/");
				strcat(inputFile,rddir->d_name);

				printf("%s\n",inputFile);
				//output 폴더의 경로를 설정해준다.

				char outputFile[50];
				outputFile[0]='\0';

				strcat(outputFile,"./");

				strcat(outputFile,argv[3]);
				strcat(outputFile,"/");
				strcat(outputFile,rddir->d_name);

				//파일 복사 함수를 호출한다.
				CopyFile(inputFile,outputFile);
			}
		}
		}
		}

	return 0;

}
	
