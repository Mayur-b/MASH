#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>

int main(int argc, char** argv)
{
	if(argc<2)
	{
		printf("Incorrect Command-Line arguements.\n");
		return -1;
	}
	int i;
	for(i=0; i<argc; i++)
	{

		if((access(argv[i],F_OK)) == -1)
		{
			printf("File does not exist.\n");
			return -1;
		}
	
		if((access(argv[i],X_OK)) == -1)
		{
			printf("File Cannot be removed.\n");
			return -1;
		}
	
		if( (unlink(argv[i])) == -1)
		{
			printf("File Cannot be removed.\n");
			return -1;
		}
	}
	return 0;
}
