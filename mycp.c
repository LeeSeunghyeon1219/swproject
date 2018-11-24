#define SIZE 1024

#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

#include <dirent.h>

int main(int argc, char *argv[]){

	if(argc<3){
		perror("argument 부족\n");
		exit(0);
	}
	
	if(argc==3){
		//파일 복사하기
		printf("파일 복사\n");

		struct stat frstatbuf;
		FILE* fr=fopen(argv[1],"r");
	
		if(fr==NULL){
			perror("read file 읽기 오류\n");
			exit(0);
		}

		int frfd=fileno(fr);

		fstat(frfd,&frstatbuf);

//	switch(frstatbuf.st_mode & S_IFMT){
//		case S_IFREG: printf("regular file\n");
//			      break;
//	}

	FILE* fw=fopen(argv[2],"w+");

	
	if(fw==NULL){
		perror("write file 열기 오류\n");
		exit(0);
	}
	

	int fwfd=fileno(fw);

//	fchmod(fwfd,frstatbuf.st_mode&(S_IRWXU|S_IRWXG|S_IRWXO));
	fchmod(fwfd,frstatbuf.st_mode);
	
	
	char buf[1024];

	while(1){
		int n=fread(buf,sizeof(char),SIZE,fr);
	//	printf("%s\n",buf);

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

	if(argc==4){
		if(strcmp(argv[1],"-r")==0){
			printf("폴더복사\n");
			
			DIR* inputdir;
			inputdir=opendir(argv[2]); //폴더를 연다


			//폴더를 읽는다 
			struct dirent * rddir=readdir(inputdir);

			if(rddir==NULL){
				//directory stream 끝에 도달하거나 에러 발생하면 0
				exit(0);
			}
			//정상적으로 폴더를 읽었으면 폴더 속 파일이름  출력
			printf("%s\n",rddir->d_name);

			}

		}

	return 0;

}
	
