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

void* EXPERIMENTAL_init(){
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
    int am = ay * ax;
    refresh();
    WINDOW *banner = newwin(1, 80, 0, 0); //need to future proof these later
    WINDOW *textfield = newwin(1, 80, 23, 0);
    WINDOW *console = newwin(21, 80, 1, 0);
    scrollok(console,TRUE);
    /** REMEMBER: terminal coordinates are index 0.
            To calculate the actual coordinates from getmaxyx(), the variables it is
        stored within should be subtracted by one.
            Additionally, y=0&x=0 is invalid. Don't try to print to those coordinates. There
        must be at least one coordinate which is above zero. The y coordinate probably, I can't
        see much of a use for only x being nonzero... maybe drawing columns? I don't know.
    */
    EXPERIMENTAL_printbanner(banner);
    EXPERIMENTAL_prompt(textfield);
}

/*void* EXPERIMENTAL_prompt(){
    clear();
    refresh();
    printw("Skywave Communicator v%d.%d.%d [%s %s] (%s) ", majver, minver, revision, majphase, minphase, port);
    if(dbg == true){
        printw("[debug]\n");
    }else{
        printw("[release]\n");
    }

    mvaddstr(1, 0, "Line 2: send notification.\n"); /** Except this function for some reason? */
    /*system("notify-send 'Hello world!' 'This is an example notification.' --icon=dialog-information");*/
    mvaddstr(23, 0, "Skw: ");
    getnstr(inpbuf, 32);
    EXPERIMENTAL_parse();
}

void EXPERIMENTAL_printbanner(int){
    wprintw(banner, "Skywave Communicator v0.0.190 (January 25, 2022)\n");
    wrefresh(banner);
    refresh();
    return;
}

void EXPERIMENTAL_prompt(int){
    wprintw(textfield, "Skw: ");
    move(23, 5); //same here
    wgetstr(textfield, inpbuf);
    EXPERIMENTAL_parse(console);
}

void* EXPERIMENTAL_parse(int){
    if(strncmp(inpbuf, "test", 32) == 0){
    	clearinpbuf();
    	EXPERIMENTAL_test(console, textfield);
    	/*printw("\ntest command\n");
        clearinpbuf();
        EXPERIMENTAL_prompt();*/
    }else if(strncmp(inpbuf, "help", 32) == 0){
    	clearinpbuf();
        EXPERIMENTAL_help(console, textfield);
    }else if(strncmp(inpbuf, "version", 32) == 0){
    	clearinpbuf();
        EXPERIMENTAL_version(console, textfield);
    }else if(strncmp(inpbuf, "changelog", 32) == 0){
    	clearinpbuf();
        EXPERIMENTAL_changelog(console, textfield);
    }else if(strncmp(inpbuf, "credits", 32) == 0){
    	clearinpbuf();
        EXPERIMENTAL_credits(console, textfield);
    }else if(strncmp(inpbuf, "configure", 32) == 0){
    	clearinpbuf();
        EXPERIMENTAL_configure(console, textfield);
    }else if(strncmp(inpbuf, "saveconfig", 32) == 0){
    	clearinpbuf();
        saveconfig();
    }else if(strncmp(inpbuf, "loadconfig", 32) == 0){
    	clearinpbuf();
        loadconfig();
    }else if(strncmp(inpbuf, "exit", 32) == 0){
    	clearinpbuf();
        EXPERIMENTAL_exit_confirmation(console, textfield);
    }else if(dbg == true && strncmp(inpbuf, "srvtest", 32) == 0){
    	clearinpbuf();
        DEBUG_netsrv_test();
    }else if(dbg == true && strncmp(inpbuf, "clitest", 32) == 0){
    	clearinpbuf();
        DEBUG_netcli_test();
    }else{
    	clearinpbuf();
	wprintw(console, "Invalid command.\n");
    }

    clearinpbuf(); //clear inpbuf just to be sure
}

void* EXPERIMENTAL_help(int, int){
    EXPERIMENTAL_prompt(console, textfield);
}

void* EXPERIMENTAL_version(int, int){
    EXPERIMENTAL_prompt(console, textfield);
}

void* EXPERIMENTAL_changelog(int, int){
    EXPERIMENTAL_prompt(console, textfield);
}

void* EXPERIMENTAL_credits(int, int){
    EXPERIMENTAL_prompt(console, textfield);
}

void* EXPERIMENTAL_configure(int, int){
    EXPERIMENTAL_prompt(console, textfield);
}

void* EXPERIMENTAL_exit_confirmation(int, int){

    char ec;
    ec = getch();
    if(ec == 'y' || ec == 'Y'){
        EXPERIMENTAL_end();
    }else{
    EXPERIMENTAL_prompt(console, textfield);
    }
}

void* EXPERIMENTAL_end(){
    clear();
    refresh();
    echo();
    endwin();
    exitprompt();
}
