#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<utime.h>
int main(int argc, char** argv)
{
	struct utimbuf t;
	if(argc <2)
	{
		printf("Command usage error.");
		return -1;
	}

	int i;
	
	for(i=0; i<argc; i++)
	{
		if((access(argv[i], F_OK)) == 0)
		{
			t.actime=t.modtime=time(0);
			if((utime(argv[i], &t)) == -1)
			{
				printf("utime error.\n");
				return -1;
			}
		}
		else
		{
			if((creat(argv[i], 0755)) == -1)
			{
				printf("File could not be created.");
				return -1;
			}
		}
	}
}
