 #include <stdio.h> 
 #include <stdlib.h> 
 #include <sys/types.h> 
 #include <dirent.h> 
 #include <sys/stat.h> 
 #include <unistd.h> 
 #include <fcntl.h> 
 #include <sys/ioctl.h> 
  
  
 // Define the color codes as macros 
// Color source - http://jafrog.com/2013/11/23/colors-in-terminal.html
 #define RESET_COLOR "\e[m" 
 #define GREEN "\e[32;1m" 
 #define BLUE "\e[34;1m" 
  
  
 int main(int argc, char **argv) 
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
