#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <utime.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define BUFFER_MAX_LENGTH 50


typedef void (*sighandler_t)(int);
char *cwd;

static char userInput = '\0';
static char buffer[BUFFER_MAX_LENGTH];
static int bufferChars = 0;
static int cArgc=0;
static char *cArgv[10];
static int helpFlag=0;

int mycat(int argc, char** argv);
int mycp(int argc, char** argv);
int myls(int argc, char* argv[]);
int mymv(int argc, char** argv);
int myrm(int argc, char** argv);
int mytouch(int argc, char** argv);
void disp(char fl[]);
int rdlnk(int argc, char** argv);
int slink(int argc, char** argv);
void handle_signal(int signo);
void prompt();
void help();
void getCommand();
void handleCommand();
void fillCommand();
void emptyCommand();
void handleRedirection();
