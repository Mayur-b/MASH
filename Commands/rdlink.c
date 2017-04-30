#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int i,rs,s=100;
char buf[100];
void rdlnk(char fl[])
{
	rs=readlink(fl, buf, s);
	
	//printf("\n%d\n", rs);
	if(rs!=-1)
	{
		printf("%s -> ", buf);
		rdlnk(buf);
	}	
}

int main(int argc, char** argv)
{
	if(argc!=2)
	{
		printf("Usage Error.\n");
		return -1;
	}
	
	
	 
	if((access(argv[1],F_OK))==-1)
	{
		printf("File does not exist.\n");
		return -1;
	}
	
	printf("%s -> ",argv[1]);
	rdlnk(argv[1]);	

	printf("\n");
	return 0;
} 
