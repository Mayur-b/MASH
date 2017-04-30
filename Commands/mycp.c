#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>

int main(int argc, char** argv)
{
	char buf[1024];
	int reads;
	int fl1, fl2;

	if(argc!=3)
	{
		printf("Incorrect Command-Line arguements.\n");
		return -1;
	}

	if((fl1=open(argv[1], O_RDONLY, 0755))==-1)
	{
		close(fl1);
		printf("Could not open %s. \n", argv[1]);
		return -1;
	}

	if((fl2=open(argv[2], O_WRONLY | O_CREAT | 0755))==-1)
	{
		printf("Could not open %s. \n", argv[2]);
		return -1;
	}

	while((reads=read(fl1,buf,sizeof(buf))) != 0)
	{	
		write(fl2,buf,reads);
	}

	//close(fl1);
	//close(fl2);
	return 0;
}
