void handle_signal(int signo)
{
	prompt();
	fflush(stdout);
}

void prompt()
{
	cwd = getenv("PWD"); 
	printf("%s:",cwd);
	printf("<#!>");
}

void help()
{
	printf("\nHelp Menu\nPress [ESC] to quit.\n");
	printf("Limit to command is 10 words.\n");
	printf("This shell can handle Redirection. (no piplining yet)\n");
	printf("List by available user-implemented commands:\n");
	printf("1. mycat\n2. myclear\n3. mycp\n4. myls\n5. mymv\n6. mytouch\n7. myrm\n8. mymkdir\n9. rdlink\n10. slink\n");
	
}

void getCommand()
{		emptyCommand();
        while ((userInput != '\n') && (bufferChars < BUFFER_MAX_LENGTH)) 
        {
        	buffer[bufferChars++] = userInput;
            userInput = getchar();
        }
        if( ! (strcmp(buffer,"h")) || ! (strcmp(buffer,"H")))
        {
			help();
			helpFlag=1;
			return;
		}
		else if(! (strcmp(buffer,"exit")))
		{
			exit(0);
		}
        buffer[bufferChars] = '\0';
        fillCommand();
}
void fillCommand()
{
        char* bufferPointer;
        bufferPointer = strtok(buffer, " ");
        while (bufferPointer != NULL)
        {
            cArgv[cArgc++] = bufferPointer;
            bufferPointer = strtok(NULL, " ");
        }
}

void emptyCommand()
{
        while (cArgc != 0)
        {
            cArgv[cArgc] = NULL;
            cArgc--;
        }
        bufferChars = 0;
}

void handleCommand(	)
{
	if(1==helpFlag)
		return;
	pid_t pid;
	int status,ifpipe=0;
	if( (pid=fork()) < 0)
	{
		printf("forking error");
	}
	else if(0 == pid)
	{
		handleRedirection();
		if((execvp(*cArgv, cArgv))<0)
			printf("exec failed: NO SUCH COMMAND\n");
	}
	else
	{
		waitpid(pid, &status, 0);
	}

}

void handleRedirection()
{
	int fd0,fd1,i,in=0,out=0;
    char input[64],output[64];

    for(i=0; cArgv[i]!='\0'; ++i)
    {
        if(strcmp(cArgv[i],"<")==0)
        {        
            cArgv[i]=NULL;
            strcpy(input,cArgv[i+1]);
            in=2;           
        }               

        if(strcmp(cArgv[i],">")==0)
        {      
            cArgv[i]=NULL;
            strcpy(output,cArgv[i+1]);
            out=2;
        }         
    }

    if(in)
    {   

        int fd0;
        if ((fd0 = open(input, O_RDONLY, 0)) < 0) {
            perror("Couldn't open input file");
            exit(0);
        }           
        dup2(fd0, 0); // STDIN_FILENO here can be replaced by 0 

        close(fd0);
    }

    if (out)
    {

        int fd1 ;
        if ((fd1 = creat(output , 0644)) < 0) {
            perror("Couldn't open the output file");
            exit(0);
        }           

        dup2(fd1, STDOUT_FILENO); // 1 here can be replaced by STDOUT_FILENO
        close(fd1);
    }

}
