#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <malloc.h>
#include <pthread.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <curses.h>

//experimental text mode windowing ui

void* curses_init(){
    stdscr = initscr();
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
    int am = ay * ax;
    refresh();
    banner = newwin(1, 80, 0, 0); //need to future proof these later
    textfield = newwin(1, 80, 23, 0);
    console = newwin(21, 80, 1, 0);
    scrollok(console,TRUE);
    /** REMEMBER: terminal coordinates are index 0.
            To calculate the actual coordinates from getmaxyx(), the variables it is
        stored within should be subtracted by one.
            Additionally, y=0&x=0 is invalid. Don't try to print to those coordinates. There
        must be at least one coordinate which is above zero. The y coordinate probably, I can't
        see much of a use for only x being nonzero... maybe drawing columns? I don't know.
    */
    curses_printbanner();
    curses_prompt();
}

void* curses_printbanner(){
    wprintw(banner, "Skywave Communicator v0.0.190 (January 25, 2022)\n");
    wrefresh(banner);
    refresh();
    return 0;
}

void* curses_prompt(){
    move(23, 0);
    wclrtoeol(textfield);
    wprintw(textfield, "Skw: ");
    wrefresh(textfield);
    wgetstr(textfield, inpbuf);
    curses_parse();
}

void* curses_parse(){
    if(strncmp(inpbuf, "test", 32) == 0){
    	clearinpbuf();
    	curses_test();
    	/*printw("\ntest command\n");
        clearinpbuf();
        EXPERIMENTAL_prompt();*/
    }else if(strncmp(inpbuf, "help", 32) == 0){
    	clearinpbuf();
        curses_help();
    }else if(strncmp(inpbuf, "version", 32) == 0){
    	clearinpbuf();
        curses_version();
    }else if(strncmp(inpbuf, "changelog", 32) == 0){
    	clearinpbuf();
        curses_changelog();
    }else if(strncmp(inpbuf, "credits", 32) == 0){
    	clearinpbuf();
        curses_credits();
    }else if(strncmp(inpbuf, "configure", 32) == 0){
    	clearinpbuf();
        curses_configure();
    }else if(strncmp(inpbuf, "viewconfig", 32) == 0){
        clearinpbuf();
        curses_configuration();
    }else if(strncmp(inpbuf, "saveconfig", 32) == 0){
    	clearinpbuf();
        saveconfig();
    }else if(strncmp(inpbuf, "loadconfig", 32) == 0){
    	clearinpbuf();
        loadconfig();
    }else if(strncmp(inpbuf, "exit", 32) == 0){
    	clearinpbuf();
        curses_exit_confirmation();
    }else if(dbg == true && strncmp(inpbuf, "notifytest", 32) == 0){
        clearinpbuf();
        DEBUG_notifytest();
    }else if(dbg == true && strncmp(inpbuf, "srvtest", 32) == 0){
    	clearinpbuf();
        DEBUG_netsrv_test();
    }else if(dbg == true && strncmp(inpbuf, "clitest", 32) == 0){
    	clearinpbuf();
        DEBUG_netcli_test();
    }else{
    	clearinpbuf();
        wprintw(console, "Invalid command.\n");
        wrefresh(console);
        curses_prompt();
    }

    clearinpbuf(); //clear inpbuf just to be sure
}
void* curses_test(){
    wprintw(console, "Test message.\n");
    wrefresh(console);
    curses_prompt();
}

void* curses_help(){
    wprintw(console, "List of commands:\n\n");
    wprintw(console, "help      | - view this page of commands\n");
    wprintw(console, "version   | - display version string\n");
    wprintw(console, "changelog | - list changes since last version\n");
    wprintw(console, "credits   | - developers/testers & libraries\n");
    wprintw(console, "configure | - configuration utility\n");
    wprintw(console, "exit      | - quit skywave\n");
    wrefresh(console);
    curses_prompt();
}

void* curses_skw_version(){
    wattrset(console, COLOR_PAIR(2));
    wprintw(console, "Skywave Communicator v%d.%d.%d [%s %s]", majver, minver, revision, majphase, minphase);
    if(dbg == true){
        wprintw(console, " [debug]\n");
    }else{
        wprintw(console, " [release]\n");
    }
    wattrset(console, COLOR_PAIR(7));
    wrefresh(console);
    curses_prompt();
}

void* curses_changelog(){
    wprintw(console, "Changes since ~v0.0.150:\n");
    wprintw(console, "  -Overhauled UI between approx. six and twelve times\n");
    wprintw(console, "  -Bug fixes(?)\n");
    wrefresh(console);
    curses_prompt();
}

void* curses_credits(){
    wprintw(console, "Project credits:\n");
    wprintw(console, "  Absolutia (project lead)\n");
    wprintw(console, "  Zephyr (some nifty ideas that won't be implemented for 100 years)\n\n");
    wprintw(console, "Libraries used:\n");
    wprintw(console, "  ncurses, pthread\n");
    wrefresh(console);
    curses_prompt();
}

void* curses_configure(){
    wprintw(console, "[Skywave Client Configurator]\n");
    move(23, 0);
    wrefresh(console);
    wclrtoeol(textfield);
    wprintw(textfield, "Select a username: ");
    wrefresh(textfield);
    wgetnstr(textfield, inpbuf, 32);
    for(i = 0; i < 16; i++){
        localuser_name[i] = inpbuf[i];
    }
    wprintw(console, "\nYour username is: %s\n", localuser_name);
    wrefresh(console);
    curses_prompt();
}

void* curses_configuration(){
    curses_prompt();
}

void* curses_exit_confirmation(){
    wclrtoeol(textfield);
    wprintw(textfield, "Are you sure you would like to exit? [y/N]: ");
    wrefresh(textfield);
    move(23, 44);
    char ec;
    ec = getch();
    if(ec == 'y' || ec == 'Y'){
        curses_end();
    }else{
    curses_prompt();
    }
}

void* curses_end(){
    clear();
    refresh();
    echo();
    endwin();
    exitprompt();
}
