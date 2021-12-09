#include <iostream>
#include <stdio.h>
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

int main()
{
    system("clear");
    thread t1(curses_init); //run curses() on thread t1
    thread t2(skwinit); //run skywinit on thread t2
    t1.join(); //when t1 has reached the end of its function kill it
    t2.join(); //when t2 has reached the end of its function kill it
    /*exitprompt(); //after all threads have merged again with the main thread, call the exit splash*/
}
