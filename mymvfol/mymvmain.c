#include "../include/mymv.h"

int main(int argc, char *argv[]){

	if(argc<3){
		perror("argument 부족\n");
		exit(0);
	}
	
	if(argc==3){

		//argv[1]은 입력파일 이고 argv[2]는 출력 폴더인지 출력 파일인지 확인한다.
		struct stat sb;
		stat(argv[2],&sb);
		
		switch(sb.st_mode & S_IFMT){

		case S_IFREG:
		//argv[2]가 출력 파일일 경우... 
		//파일의 이름을 바꾸는 것이 됨!
		MVFile(argv[1],argv[2]); 

		break;

		case S_IFDIR:

		//argv[2]가 출력 폴더일 경우
		//argv[2] 폴더 밑에 argv[1] 파일을 만듦
		
		sprintf(buf,"./%s/%s",argv[2],argv[1]);
		fopen(buf,"w+");
		MVFile(argv[1],buf);

		break;
}
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
				
				int res=MVfolderCopy(inputdir,outputdir);
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
				
				int res=MVfolderCopy(inputdir,outputdir);
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
					}	
		}
		}
	return 0;

}
