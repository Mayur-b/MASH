void handle_signal(int signo)
{
	printf("\n<#!>");
	fflush(stdout);
}

void prompt()
{
	printf("<#!>");
}

void help()
{
	printf("Help Menu\nPress [ESC] to quit.\n");
	printf("Limit to command is 10 words.\n");
	
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
	pid_t pid;
	int status;
	if( (pid=fork()) < 0)
	{
		printf("forking error");
	}
	else if(0 == pid)
	{
		if((execvp(*cArgv, cArgv))<0)
			{
				printf("exec failed: NO SUCH COMMAND\n");
			}
	}
	else
	{
		waitpid(pid, &status, 0);
	}

}
