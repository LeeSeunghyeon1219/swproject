#include "../include/mycp.h"


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
			//exit(0);
			return ;
	}

		fwrite(buf,sizeof(char),n,fw);
	}

	 fclose(fr);
	 fclose(fw);

}

