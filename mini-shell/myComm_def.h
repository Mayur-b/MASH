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

#define RESET_COLOR "\e[m" 
#define GREEN "\e[32;1m" 
#define BLUE "\e[34;1m" 
  
  
 int myls(int argc, char **argv) 
 { 
    char *cwd = NULL; 
    DIR *dp = NULL; 
    struct dirent *dptr = NULL; 
    unsigned int count = 0; 
  
    cwd = getenv("PWD"); 
    if(NULL == cwd) 
    { 
        printf("\n ERROR : Could not get the working directory\n"); 
        return -1; 
    }
    
    //check if no directory argument is given, then load current working directory, otherwise use the argument mentioned
    if(argc==1) 
        dp = opendir(cwd);       
    else 
        dp = opendir(argv[1]);
    

    if(NULL == dp) 
    { 
        printf("\n ERROR : Could not open the working directory\n"); 
        return -1; 
    } 
   
    for(count = 0; NULL != (dptr = readdir(dp)); count++) 
    { 
        if(dptr->d_name[0] != '.') 
        { 
            // Check if the file is executable 
            if(!access(dptr->d_name,X_OK)) 
            { 
                int fd = -1; 
                struct stat st; 
  
                fd = open(dptr->d_name, O_RDONLY, 0); 
                if(-1 == fd) 
                { 
                    printf("\n Opening file/Directory failed\n"); 
                    return -1; 
                } 
                 
                fstat(fd, &st); 
                if(S_ISDIR(st.st_mode)) // Check if it actaully was a directory with execute  permissions on it.  
                    printf(BLUE"%s   "RESET_COLOR,dptr->d_name); // If it was a directory, print it in Blue
                else 
                    printf(GREEN"%s   "RESET_COLOR,dptr->d_name); // If it was a normal executable Print it in green 
                close(fd); 
            } 
            else 
                printf("%s   ",dptr->d_name); // No executable flag ON Print it in black(default) 
        } 
    } 
    printf("\n"); 
  
    return 0; 
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

int myclear(void)
{
    printf("\033[H\033[2J");
    return 0;
}
