#include "../include/mymv.h"

void MVFile(char* inputFile, char* outputFile){

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

