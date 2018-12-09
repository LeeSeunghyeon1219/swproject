#include "../include/mycp.h"

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
					printf("폴더명: %s", outbuf);
					perror("폴더를 만들지 못하였습니다.\n");
					printf("%d: %s\n",errno,strerror(errno));

					return 0;
					}


				DIR* indir=opendir(inbuf);
				DIR* outdir=opendir(outbuf);

				folderCopy(indir,outdir);

				//재귀함수 빠져나오면 서브 폴더 경로 빼주기
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
