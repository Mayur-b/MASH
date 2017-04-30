#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main(int argc, char** argv)
{
	if(argc!=3)
	{
		printf("Usage Error.\n");
		return -1;
	}
	
	if((access(argv[1],F_OK))==-1)
	{
		printf("File %s does not exist.\n", argv[1]);
		return -1;
	}
	
	if((symlink(argv[1],argv[2]))==-1)
	{
		printf("Linking Error.\n");
		return -1;
	}
	
return 0;
}
