#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <pthread.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <curses.h>

void* loadconfig(){

    if(expui == true){
        return 0;
    }else{
        curses_prompt();
    }
}

void* saveconfig(){
    if(expui == true){
        return 0;
    }else{
        if(strlen(localuser_name) <= 0 || strlen(localuser_name) <= 0){
            printw("Fatal error: localuser_name is undefined or of zero length.\n");
            curses_prompt();
        }

        printw("Create file pointer pFile.\n");
        FILE *pFile;
        printw("Open file conf.conf.\n");
        pFile = fopen("conf.conf","w");
        printw("Write data: strlen(localuser_name): %d, localusername: [%-1.24s]\n", strlen(localuser_name), localuser_name);
        fprintf(pFile, "%d[%-1.24s]", strlen(localuser_name), localuser_name);
        fclose(pFile);
        curses_prompt();
    }
}
