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

#include <skw_define.h>
#include <skw_debug.h>

#include <skw_cursesui.h>
#include <skw_fileio.h>
#include <skw_network.h>

void clearinpbuf(){
    memset(inpbuf,0,sizeof(inpbuf));
    return;
}

void configuration_autoload(){
    //temporary stub
    return;
}

void* exitprompt(){
    system("clear");
    printf("Thank you for using Skywave!\n");
    system("sleep 3");
    exit(0);
}

int main(int argc, char *argv[])
{
    system("clear");
    curses_init();
    /*Got rid of threading code here,
    new threads will be spawned as needed from the curses session.*/
}
