#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	struct stat st = {0};
	int status=-999;
	if(argc<2)
		printf("Command ussage error. Expected: mymkdir dir-name[s]\n");
	else
	{
		int i=1;
		while(i<=argc-1)
		{
			if (stat(argv[i], &st) == -1)
			{
				status= mkdir(argv[i], 0777);
				if( status == -1)
				{
					printf("Could not make directory %s\n", argv[i]);
				}
			}
			++i;
		}
	}
}