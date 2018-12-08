
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char * argv[])
{
	unlink(argv[1]);
	return 0;
}
