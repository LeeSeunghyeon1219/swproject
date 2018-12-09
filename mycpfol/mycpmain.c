#include "../include/mycp.h"



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

				inputFile[0]='\0';

				strcat(inputFile,"./");

				strcat(inputFile,argv[2]);

				outputFile[0]='\0';

				strcat(outputFile,"./");

				strcat(outputFile,argv[3]);

				int res=folderCopy(inputdir,outputdir);
				if(res==0){
					printf("cp실패!\n");
				}
				else{
					printf("cp성공!\n");
				}	}
		}

	return 0;

}
