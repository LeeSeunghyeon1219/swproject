#define SIZE 1024

#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>



int main(int argc, char *argv[]){

	if(argc!=3){
		perror("argument 부족\n");
		exit(0);
	}

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

	fchmod(fwfd,frstatbuf.st_mode&(S_IRWXU|S_IRWXG|S_IRWXO));
	
	
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
	return 0;

}
	
