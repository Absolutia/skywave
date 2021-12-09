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

//experimental text mode windowing ui

void EXPERIMENTAL_init(){
    initscr();
    clear();
    refresh();
    raw();
    printw("Please wait...\n");
    if(has_colors()){
        start_color();

        //initialize some basic curses pallettes
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);
        init_pair(4, COLOR_BLUE, COLOR_BLACK);
        init_pair(5, COLOR_CYAN, COLOR_BLACK);
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(7, COLOR_WHITE, COLOR_BLACK);
    }
    refresh();
    while(t_init == true){
        t_crsrdy = true;
    }
    clear();
    getmaxyx(stdscr, ay, ax);
    return;
}
