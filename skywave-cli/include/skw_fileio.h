#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <pthread.h>
#include <curses.h>

void* loadconfig(){
    //blah
    curses_cmdprompt();
}

void* saveconfig(){
    if(strlen(localuser_name) <= 0 || strlen(localuser_name) <= 0){
        wprintw(console, "Fatal error: localuser_name is undefined or of zero length.\n");
        wrefresh(console);
        refresh();
        curses_cmdprompt();
    }

    wprintw(console, "Create file pointer pFile.\n");
    wrefresh(console);
    FILE *pFile;
    wprintw(console, "Open file conf.conf.\n");
    wrefresh(console);
    pFile = fopen("conf.conf","w");
    wprintw(console, "Write data: strlen(localuser_name): %d, localusername: [%-1.24s]\n", strlen(localuser_name), localuser_name);
    wrefresh(console);
    fprintf(pFile, "%d[%-1.24s]", strlen(localuser_name), localuser_name);
    fclose(pFile);
    curses_cmdprompt();
}
