int mycat(int argc, char** argv)
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

int mycp(int argc, char** argv)
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

int myls(int argc, char* argv[])
{
    DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;

    char buf[512];
    mydir = opendir(argv[1]);
    while((myfile = readdir(mydir)) != NULL)
    {
        sprintf(buf, "%s/%s", argv[1], myfile->d_name);
        stat(buf, &mystat);
        printf("%zu",mystat.st_size);
        printf(" %s\n", myfile->d_name);
    }
    closedir(mydir);
}

int mymv(int argc, char** argv)
{
	char buf[1024];
	int reads;
	int fl1, fl2;

	if(argc!=3)
	{
		printf("Incorrect Command-Line arguements.\n");
		return -1;
	}

	if((access(argv[1],F_OK)) == -1)
	{
		printf("File %s does not exist.\n", argv[1]);
		return -1;
	}
	
	if((access(argv[1],R_OK)) == -1)
	{
		printf("Read permission denied.\n");
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

	if( (unlink(argv[1])) == -1)
	{
		printf("Partial Fail.\n");
		return -1;
	}
	//close(fl1);
	//close(fl2);
	return 0;
}

int myrm(int argc, char** argv)
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

int mytouch(int argc, char** argv)
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


int i,rs,s=100; 
char buf[100];
void disp(char fl[])
{
	rs=readlink(fl, buf, s);
	
	//printf("\n%d\n", rs);
	if(rs!=-1)
	{
		printf("%s -> ", buf);
		disp(buf);
	}	
}

int rdlnk(int argc, char** argv)
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
	disp(argv[1]);	

	printf("\n");
	return 0;
} 

int slink(int argc, char** argv)
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