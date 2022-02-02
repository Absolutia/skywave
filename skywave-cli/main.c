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

void* skwinit(){
    if(t_init == true){
    //uh, why does this still exist?
    }
    t_init = false;
}

void configuration_autoload(){
    return;
}

void* exitprompt(){
    system("clear");
    printf("Thank you for using Skywave!\n");
    system("sleep 3");
    exit(0);
}

void* inet(){
    //when ready to attempt connection this function should run on a new thread

    //check contarget
    //attmpt handshake with target
    //attmpt to conn if protocol supported
    /** obviously not yet implemented */
}

int main(int argc, char *argv[])
{
    system("clear");
    curses_init();
    /*if(expui == true){
        pthread_t cursesui;
        pthread_create(&cursesui, NULL, EXPERIMENTAL_init, NULL);
        pthread_join(cursesui, NULL);
    }else{
        pthread_t cursesui;
        pthread_create(&cursesui, NULL, curses_init, NULL);
        pthread_join(cursesui, NULL);
    }*/
    /*exitprompt(); //after all threads have merged again with the main thread, call the exit splash*/
}
