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

void curses_init(){
    initscr();
    raw();
    clear();
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
    /*while(t_init == true){
        t_crsrdy = true;
    }*/
    curses_splash();
}

void curses_splash(){
    clear();
    curses_skw_version();
    curses_prompt();
}

void curses_prompt(){
    echo();
    printw("Skw: ");
    getnstr(inpbuf, 32); /* when dealing with input functions,
    need to take care to properly handle buffer overflows in the future */
    refresh();
    curses_parse();
}

void curses_parse(){
    //lol i broke this function [curses_parse() in case it wasnt obvious] while i was trying to fix an issue that wasn't really an issue
    if(strncmp(inpbuf, "test", 32) == 0){
        printw("\ntest command\n");
        clearinpbuf();
        curses_prompt();
    }else if(strncmp(inpbuf, "help", 32) == 0){
        clearinpbuf();
        curses_help();
    }else if(strncmp(inpbuf, "version", 32) == 0){
        clearinpbuf();
        curses_skw_version();
    }else if(strncmp(inpbuf, "changelog", 32) == 0){
        clearinpbuf();
        curses_changelog();
    }else if(strncmp(inpbuf, "credits", 32) == 0){
        clearinpbuf();
        curses_credits();
    }else if(strncmp(inpbuf, "configure", 32) == 0){
        clearinpbuf();
        curses_configure();
    }else if(strncmp(inpbuf, "saveconfig", 32) == 0){
        clearinpbuf();
        saveconfig();
    }else if(strncmp(inpbuf, "loadconfig", 32) == 0){
        clearinpbuf();
        loadconfig();
    }else if(strncmp(inpbuf, "exit", 32) == 0){
        clearinpbuf();
        curses_exit_confirmation();
    }else if(dbg == true && strncmp(inpbuf, "srvtest", 32) == 0){
        clearinpbuf();
        DEBUG_netsrv_test();
    }else if(dbg == true && strncmp(inpbuf, "clitest", 32) == 0){
        clearinpbuf();
        DEBUG_netcli_test();
    }else{
        clearinpbuf();
        printw("Invalid command.\n");
    }

    //now we clear the input buffer
    clearinpbuf();
    curses_prompt();
}

void curses_help(){
    printw("List of commands:\n\n");
    printw("help      | - view this page of commands\n");
    printw("version   | - display version string\n");
    printw("changelog | - list changes since last version\n");
    printw("credits   | - developers/testers & libraries\n");
    printw("configure | - configuration utility\n");
    printw("exit      | - quit skywave\n");
    refresh();
    curses_prompt();
}

void curses_skw_version(){
    printw("Skywave Communicator v%d.%d.%d [%s %s] (%s) ", majver, minver, revision, majphase, minphase, port);
    if(dbg == true){
        printw("[debug]\n");
    }else{
        printw("[release]\n");
    }
    return;
}

void curses_changelog(){
    printw("tbd here\n");
    refresh();
    curses_prompt();
}

void curses_credits(){
    clear();
    refresh();
    curses_skw_version();
    printw("Project credits:\n\n");
    printw("Absolutia (project lead)\n");
    printw("Zephyr (some nifty ideas that won't be implemented for 100 years)\n");
    refresh();
    sleep(5);
    curses_prompt();
}

void curses_configure(){
    clear();
    refresh();
    printw("[Skywave Client Configurator]\n\n");
    printw("Select a username: ");
    getnstr(inpbuf, 32);
    for(i = 0; i < 16; i++){
        localuser_name[i] = inpbuf[i];
    }
    printw("\nYour username is: %s\n", localuser_name);
    curses_prompt();
}

void curses_p2p_chatsession(){
    curses_prompt();
}

void curses_exit_confirmation(){
    printw("Are you sure you want to exit?\n");
    printw("[y/N] ");
    char ec;
    ec = getch();
    if(ec == 'Y' || ec == 'y'){
        curses_end();
    }else{
        curses_prompt();
    }
}

void curses_end(){
    clear();
    refresh();
    echo();
    endwin();
    exitprompt();
}
