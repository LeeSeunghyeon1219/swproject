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



char inputFile[50];
char outputFile[50];
				
char inbuf[1024];
char outbuf[1024];
				

char intemp[1024];							
char outtemp[1024];
				
		
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

			int val= unlink(inputFile);
		

			if(val==0){
				printf("입력 파일 :%s 지우기 성공\n",inputFile);
			}
			else{
				printf("입력 파일 삭제 실패 :%s , 이유 %s\n", inputFile,strerror(errno));
			}
			
			 fclose(fr);
			 fclose(fw);

			return ;		
	}

		fwrite(buf,sizeof(char),n,fw);
	}
	
	
	


}

int folderCopy(DIR* inputdir,DIR* outputdir){


			while(1){

			struct dirent * rddir=readdir(inputdir);
			
			struct dirent * outrddir=readdir(outputdir);
			
		
			if(rddir==NULL){
				//directory stream 끝에 도달하거나 에러 발생하면 0
			
				printf("mycp끝\n");
				return 1;
			}


			//파일인지 폴더인지 확인
		
			if(rddir->d_type == DT_DIR){
				//폴더이다.

				if(strcmp(rddir->d_name,".")==0 || strcmp(rddir->d_name,"..")==0){
				//do nothing.
				}

				

				else{


				printf("폴더명: %s",rddir->d_name);
			
				printf("폴더입니다\n");
			

				//폴더 복사를 위해서 재귀함수를 호출한다.
				
				
				sprintf(inbuf,"%s/%s",inputFile,rddir->d_name);
				sprintf(outbuf,"%s/%s",outputFile,rddir->d_name);

				printf("재귀 함수 호출 - 입력 폴더:%s\n",inbuf);
				printf("재귀 함수 호출 - 출력 폴더:%s\n",outbuf);


				//input 폴더를 복제할 output 폴더를 만든다.
		 			struct stat buf;
					stat(inbuf,&buf);
				int mkdirFlag=mkdir(outbuf,buf.st_mode); 
				
			
				if(mkdirFlag==0){
					printf("output 폴더 만들기 성공하였습니다.\n");
					//서브 폴더 경로도 붙여주기
					strcpy(intemp,inputFile);
					strcpy(outtemp,outputFile);

					strcpy(inputFile,inbuf);
					strcpy(outputFile,outbuf);
					}

				else{
					printf("폴더명: %s\n", outbuf);
					perror("폴더를 만들지 못하였습니다.\n");
					printf("%s\n",strerror(errno));
				
					strcpy(intemp,inputFile);
					strcpy(outtemp,outputFile);

					strcpy(inputFile,inbuf);
					strcpy(outputFile,outbuf);
					
					}


				DIR* indir=opendir(inbuf);
				DIR* outdir=opendir(outbuf);

				folderCopy(indir,outdir);
				
				//재귀함수 빠져나오면 서브 폴더 경로 빼주기
				
				//mv이므로 입력파일의 subdirectory 삭제
				int val=rmdir(inputFile);
				if(val==0){
					printf("입력 폴더 :%s 지우기 성공\n",inputFile);
				}
				else{
					printf("입력 폴더 삭제 실패 :%s , 이유 %s\n", inputFile,strerror(errno));
				}

				strcpy(inputFile,intemp);
				strcpy(outputFile,outtemp);
				

				}}
		else if(rddir->d_type==DT_REG){
				//regular file이면 파일복사를 한다.

				//파일 이름을 출력한다.
				printf("파일 입니다 : %s\n",rddir->d_name);
			
				//input 폴더의 경로를 설정해준다.
			

				char ref[1024];

				sprintf(ref,"%s/%s",inputFile,rddir->d_name);


				printf("%s\n",ref);
				//output 폴더의 경로를 설정해준다.
				
				char outref[1024];

				sprintf(outref,"%s/%s",outputFile,rddir->d_name);
				//파일 복사 함수를 호출한다.

				
				CopyFile(ref,outref);
			}
	}
	return 1;

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


		if(strcmp(argv[1],"-m")==0){
				
			DIR* inputdir;
			inputdir=opendir(argv[2]); //input 폴더를 연다
	
			//input폴더를 읽는 다 
			
			//input 폴더를 복제할 output 폴더를 만든다.
		 	struct stat buf;
			stat(argv[2],&buf);
			int mkdirFlag=mkdir(argv[3],buf.st_mode); 



			if(mkdirFlag==0){
				printf("output 폴더 만들기 성공하였습니다.\n");
				
			}

			else{
				perror("폴더를 만들지 못하였습니다.\n");
				printf("%s\n",strerror(errno));
				
				}


				DIR* outputdir;
				outputdir=opendir(argv[3]);
				
				inputFile[0]='\0';

				strcat(inputFile,"./");
				
				strcat(inputFile,argv[2]);
				
				outputFile[0]='\0';

				strcat(outputFile,"./");

				strcat(outputFile,argv[3]);
				
				int res=folderCopy(inputdir,outputdir);
				if(res==0){
					printf("mv실패!\n");
				}
				else{
					printf("mv성공!\n");

					int val=rmdir(inputFile);
					if(val==0){
						printf("입력 폴더 :%s 지우기 성공\n",inputFile);
					}
					else{
						printf("입력 폴더 삭제 실패 :%s , 이유 %s\n", inputFile,strerror(errno));
					}
					}	}
		
	



	}

	if(argc==4){
		if(strcmp(argv[1],"-r")==0){
			printf("폴더복사\n");
			
			DIR* inputdir;
			inputdir=opendir(argv[2]); //input 폴더를 연다
	
			//input폴더를 읽는nB NC 다 
			
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
				
				inputFile[0]='\0';

				strcat(inputFile,"./");
				
				strcat(inputFile,argv[2]);
				
				outputFile[0]='\0';

				strcat(outputFile,"./");

				strcat(outputFile,argv[3]);
				
				int res=folderCopy(inputdir,outputdir);
				if(res==0){
					printf("mv실패!\n");
				}
				else{
					printf("mv성공!\n");

					int val=rmdir(inputFile);
					if(val==0){
						printf("입력 폴더 :%s 지우기 성공\n",inputFile);
					}
					else{
						printf("입력 폴더 삭제 실패 :%s , 이유 %s\n", inputFile,strerror(errno));
					}
					}	}
		}
		
	return 0;

}
	
