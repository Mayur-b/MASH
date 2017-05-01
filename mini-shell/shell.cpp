#include "definitions.h"
//#include "myComm_def.h"
#include "func_def.h"



int main(int argc, char *argv[], char *envp[])
{
	printf("Welcome to my shell. \n\tEnter 'h' or 'H' for help\n\n");
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, handle_signal);
	prompt();
	while(true) 
	{
		userInput = getchar();
		switch(userInput)
		{
			case '\n':	prompt();
					break;
			case 27  :	exit(0);
					break;

			default  :	getCommand();
					handleCommand();
					prompt(); 
					break;
		}
		
	}
	printf("\n");
	return 0;
}
