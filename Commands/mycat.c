#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("Wrong usage of command.\n\n");
		return -1;
	}

	if((access(argv[1],F_OK)) == -1)
	{
		printf("File does not exist.\n\n");
		return -1;
	}

	if((access(argv[1],R_OK)) == -1)
	{
		printf("Read access denied..\n\n");
		return -1;
	}

	int fl, reads;
	char buff[1024];

	if((fl=open(argv[1], O_RDONLY, 0755)) == -1)
	{
		printf("Could not open file.\n\n");
		return -1;
	}
	
	while((reads=read(fl,buff,sizeof(buff))) > 0);
	{
		printf("%s", buff);
	}
	printf("\n");	
	return 0;
}
