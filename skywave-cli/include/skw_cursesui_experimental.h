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

char scrnbuf[1920];

int twoy = 24;
int twox = 1;

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
    /*while(t_init == true){
        t_crsrdy = true;
    }*/
    clear();
    getmaxyx(stdscr, ay, ax); //y is height in rows, x is width in columns
    /*WINDOW *textfield = newwin(1, 80, twoy, twox);*/
    refresh();
    EXPERIMENTAL_prompt();
}

void EXPERIMENTAL_prompt(){
    clear();
    refresh();
    printw("Skywave Communicator v%d.%d.%d [%s %s] (%s) ", majver, minver, revision, majphase, minphase, port);
    if(dbg == true){
        printw("[debug]\n");
    }else{
        printw("[release]\n");
    }
    /** REMEMBER: terminal coordinates are index 0.
            To calculate the actual coordinates from getmaxyx(), the variables it is
        stored within should be subtracted by one.
            Additionally, y=0&x=0 is invalid. Don't try to print to those coordinates. There
        must be at least one coordinate which is above zero. The y coordinate probably, I can't
        see much of a use for only x being nonzero... maybe drawing columns? I don't know.
    */
    mvaddstr(1, 0, "Line 2: send notification.\n");
    system("notify-send 'Hello world!' 'This is an example notification.' --icon=dialog-information");
    mvaddstr(23, 0, "Skw: ");
    getnstr(inpbuf, 32);
    EXPERIMENTAL_parse();
}

void EXPERIMENTAL_parse(){
    if(strncmp(inpbuf, "test", 32) == 0){
    	printw("\ntest command\n");
	clearinpbuf();
	EXPERIMENTAL_prompt();
    }else if(strncmp(inpbuf, "help", 32) == 0){
    	clearinpbuf();
        EXPERIMENTAL_help();
    }else if(strncmp(inpbuf, "version", 32) == 0){
    	clearinpbuf();
        EXPERIMENTAL_version();
    }else if(strncmp(inpbuf, "changelog", 32) == 0){
    	clearinpbuf();
        EXPERIMENTAL_changelog();
    }else if(strncmp(inpbuf, "credits", 32) == 0){
    	clearinpbuf();
        EXPERIMENTAL_credits();
    }else if(strncmp(inpbuf, "configure", 32) == 0){
    	clearinpbuf();
        EXPERIMENTAL_configure();
    }else if(strncmp(inpbuf, "saveconfig", 32) == 0){
    	clearinpbuf();
        saveconfig();
    }else if(strncmp(inpbuf, "loadconfig", 32) == 0){
    	clearinpbuf();
        loadconfig();
    }else if(strncmp(inpbuf, "exit", 32) == 0){
    	clearinpbuf();
        EXPERIMENTAL_exit_confirmation();
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

    clearinpbuf(); //clear inpbuf just to be sure
}

void EXPERIMENTAL_help(){
    EXPERIMENTAL_prompt();
}

void EXPERIMENTAL_version(){
    EXPERIMENTAL_prompt();
}

void EXPERIMENTAL_changelog(){
    EXPERIMENTAL_prompt();
}

void EXPERIMENTAL_credits(){
    EXPERIMENTAL_prompt();
}

void EXPERIMENTAL_configure(){
    EXPERIMENTAL_prompt();
}

void EXPERIMENTAL_exit_confirmation(){
    mvaddstr(22, 0, "Are you sure you want to exit? [y/N]: ");
    char ec;
    ec = getch();
    if(ec == 'y' || ec == 'Y'){
        EXPERIMENTAL_end();
    }
}

void EXPERIMENTAL_end(){
    clear();
    refresh();
    echo();
    endwin();
    exitprompt();
}
