#include <iostream>
#include <stdio.h>
#include <stdbool.h>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <string>
#include <math.h>
#include <random>
#include <chrono>
#include <atomic>
#include <thread>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <argp.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <curses.h>
#include <skw_define.h>
#include <skw_debug.h>

#include <skw_cursesui_plain.h>
#include <skw_cursesui_experimental.h>
#include <skw_network.h>

void clearinpbuf(){
    memset(inpbuf,0,sizeof(inpbuf));
    return;
}

void skwinit(){
    if(t_init == true){
    //uh, why does this still exist?
    }
    t_init = false;
}

void configuration_autoload(){
    return;
}

void exitprompt(){
    system("clear");
    cout << "Thank you for using Skywave!\n";
    system("sleep 3");
    exit(0);
}

void inet(){
    //when ready to attempt connection this function should run on a new thread

    //check contarget
    //attmpt handshake with target
    //attmpt to conn if protocol supported
    /** obviously not yet implemented */
}

int main(int argc, char *argv[])
{
    system("clear");
    if(expui == true){
        thread t1(EXPERIMENTAL_init);
        t1.join();
    }else{
        thread t1(curses_init);
        t1.join();
    }
    /*exitprompt(); //after all threads have merged again with the main thread, call the exit splash*/
}
