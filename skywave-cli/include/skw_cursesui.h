#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <malloc.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <pthread.h>
#include <curses.h>

//text mode ui

void* curses_init(){
    printf("Please wait...");
    stdscr = initscr();
    clear();
    refresh();
    raw();
    if(has_colors()){
        csupport = true;
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
    keypad(stdscr,TRUE);
    if(has_key(0411) && has_key(0412) && has_key(0413) && has_key(0414) && has_key(0415) && has_key(0416) && has_key(0417) && has_key(0420) && has_key(0421) && has_key(0422) && has_key(0423) && has_key(0424)){
	fsupport = 12;
	if(dbg == true){
		printf("Terminal supports all 12 function keys.\n");
	}
    }else{
    	ecode = 2;
	curses_end();
    }
    refresh();
    /*while(t_init == true){
        t_crsrdy = true;
    }*/
    clear();
    getmaxyx(stdscr, ay, ax); //y is height in rows, x is width in columns
    refresh();
    //old window definitions, only use if something broke with the new ones
    /*versionbanner = newwin(1, 80, 0, 0); //need to future proof these later
    textfield = newwin(1, 80, 23, 0);
    console = newwin(21, 80, 2, 0);
    connectbanner = newwin(1, 80, 1, 0);*/

    //new windowing
    //newwin(int size_y, int size_x, int origin_y, int origin_x);
    versionbanner = newwin(1, ax, 0, 0);
    connectbanner = newwin(1, ax, 1, 0);
    console = newwin(ay - 2, ax, 2, 0);
    //since textfield is to be overlayed over something, do i extend the console
    //and channel windows or do i use it to echo key combos while in combo mode?
    textfield = newwin(1, ax, ay - 1, 0);
    scrollok(console,TRUE); //scrollok(WINDOW*,bool);
    scrollok(channel1,TRUE);//WINDOW* is the respective pointer to said window
    scrollok(channel2,TRUE);//and "bool" is just TRUE or FALSE. given that its in
    scrollok(channel3,TRUE);//all caps my assumption is that "TRUE" and "FALSE"
    scrollok(channel4,TRUE);//here are macros. Don't quote me on that though.
    /** REMEMBER: window origin coordinates are index 0.
    Window size coordinates are index 1. */
    keypad(console,TRUE); //setup keypad/function keys for windows that need it
    keypad(channel1,TRUE);//when these are enabled ie getch() should return a
    keypad(channel2,TRUE);//macro beginning with "KEY_" instead of the raw id
    keypad(channel3,TRUE);//for the keys.
    keypad(channel4,TRUE);//also this may be unnecessary as according to the MAN
    keypad(textfield,TRUE);//page there's only one input queue for all windows.
    curses_printbanner();
    curses_printconnect();
    //oobe should only be true if this is your first time running skywave
    if(oobe == true){
    	curses_oobe();
    }
    curses_cmdprompt();
}

void* curses_printbanner(){
    wprintw(versionbanner, "Skywave Communicator v%d.%d.%d (%s %d, %d)\n", majver, minver, revision, month, day, year);
    wrefresh(versionbanner);
    refresh();
    return 0;
}

void* curses_printconnect(){
    //setup the connection banner here
    wattrset(connectbanner, COLOR_PAIR(1));
    wprintw(connectbanner, "Not connected");
    wattrset(connectbanner, COLOR_PAIR(7));
    wprintw(connectbanner, " | ");
    wprintw(connectbanner, "Console");
    wrefresh(connectbanner);
    return 0;
}

void* curses_oobe(){
    wprintw(console, "oobe goes here lmao");
    if(dbg == true){
        wprintw(console, "\n\nDebugging printout:\n");
	wprintw(console, "Display:\n");
        wprintw(console, "displaymode = %d\n", displaymode);
        wprintw(console, "ay = %d\n", ay);
        wprintw(console, "ax = %d\n", ax);
        wprintw(console, "max_y = %d\n", max_y);
        wprintw(console, "max_x = %d\n", max_x);
	int csupportint;
	if(csupport == true){
	    csupportint = 1;
	}
        wprintw(console, "csupport = %d\n\n", csupportint);
        wprintw(console, "Input:\n");
        wprintw(console, "fsupport = %d\n", fsupport);
    }
    wrefresh(console);
    return 0;
}

void* curses_keyprompt(){
    //aaaa2
    return 0;
}

void* curses_cmdprompt(){
    move(ay, 0);
    wclrtoeol(textfield);
    wprintw(textfield, "Skw: ");
    wrefresh(textfield);
    wgetstr(textfield, inpbuf);
    curses_cmdparse();
}

void* curses_dbgprompt(){
    return 0;
}

void* curses_cmdparse(){
    if(strncmp(inpbuf, "test", 32) == 0){
    	clearinpbuf();
    	curses_test();
    	/*printw("\ntest command\n");
        clearinpbuf();
        EXPERIMENTAL_prompt();*/
    }else if(strncmp(inpbuf, "clearconsole", 32) == 0){
        clearinpbuf();
        wclear(console);
        wrefresh(console);
        curses_cmdprompt();
    }else if(strncmp(inpbuf, "cmdhelp", 32) == 0){
    	clearinpbuf();
        curses_cmdhelp();
    }else if(strncmp(inpbuf, "dbghelp", 32) == 0){
    	clearinpbuf();
	curses_dbghelp();
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
    }else if(strncmp(inpbuf, "viewconfig", 32) == 0){
        clearinpbuf();
        curses_viewconfig();
    }else if(strncmp(inpbuf, "saveconfig", 32) == 0){
    	clearinpbuf();
        saveconfig();
    }else if(strncmp(inpbuf, "loadconfig", 32) == 0){
    	clearinpbuf();
        loadconfig();
    }else if(strncmp(inpbuf, "connect", 32) == 0){
        clearinpbuf();
        connectmenu();
    }else if(strncmp(inpbuf , "chwin", 32) == 0){
        clearinpbuf();
        curses_chwin();
    }else if(strncmp(inpbuf, "exit", 32) == 0){
    	clearinpbuf();
        curses_exit_confirmation();
    }else if(dbg == true && strncmp(inpbuf, "debug_p2phost", 32) == 0){
        clearinpbuf();
        iret2 = pthread_create(&p2p_netsrv, NULL, TEST_netinit_server, NULL);
        curses_cmdprompt();
    }else if(dbg == true && strncmp(inpbuf, "notifytest", 32) == 0){
        clearinpbuf();
        DEBUG_notifytest();
    }else if(dbg == true && strncmp(inpbuf, "terminfo", 32) == 0){
        clearinpbuf();
        DEBUG_terminfo();
    }else if(dbg == true && strncmp(inpbuf, "keytest_echo", 32) == 0){
        clearinpbuf();
        DEBUG_keytest_echo();
    }else if(dbg == true && strncmp(inpbuf, "keytest_noecho", 32) == 0){
        clearinpbuf();
        DEBUG_keytest_noecho();
    }else{
    	clearinpbuf();
        wprintw(console, "Invalid command.\n");
        wrefresh(console);
        curses_cmdprompt();
    }

    clearinpbuf(); //clear inpbuf just to be sure
}
void* curses_test(){
    wprintw(console, "Test message.\n");
    wrefresh(console);
    curses_cmdprompt();
}

void* curses_cmdhelp(){
    wprintw(console, "\nList of commands:\n\n");
    wprintw(console, "clearconsole | - clear the main console\n");
    wprintw(console, "help         | - view this page of commands\n");
    wprintw(console, "version      | - display version string\n");
    wprintw(console, "changelog    | - list changes since last version\n");
    wprintw(console, "credits      | - developers/testers & libraries\n");
    wprintw(console, "configure    | - configuration utility\n");
    wprintw(console, "saveconfig   | - save configuration in memory\n");
    wprintw(console, "loadconfig   | - load configuration from disk\n");
    wprintw(console, "connect      | - connect to a target\n");
    wprintw(console, "exit         | - quit skywave\n");
    wrefresh(console);
    curses_cmdprompt();
}

void* curses_dbghelp(){
    wprintw(console, "\nList of debugging commands:\n\n");
    wprintw(console, "notifytest | - test DE push notification support\n");
    wprintw(console, "terminfo   | - display info about the current curses enviroment\n");
    wrefresh(console);
    curses_cmdprompt();
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
    curses_cmdprompt();
}

void* curses_changelog(){
    wprintw(console, "\nChanges since v0.0.190:\n");
    wprintw(console, "  -Preliminary networking\n");
    wprintw(console, "  -UI improvements\n");
    wprintw(console, "  -Bug fixes\n");
    wrefresh(console);
    curses_cmdprompt();
}

void* curses_credits(){
    wprintw(console, "\nProject credits:\n");
    wprintw(console, "  Absolutia (project lead)\n");
    wprintw(console, "  Zephyr (some nifty ideas that won't be implemented for 100 years)\n\n");
    wprintw(console, "Libraries used:\n");
    wprintw(console, "  ncurses, pthread\n");
    wrefresh(console);
    curses_cmdprompt();
}

void* curses_configure(){
    //wprintw(console, "[Skywave Client Configurator]\n");
    move(ay, 0);
    wrefresh(console);
    wclrtoeol(textfield);
    wprintw(textfield, "Select a username: ");
    wrefresh(textfield);
    clearinpbuf();
    wgetnstr(textfield, inpbuf, 32);
    for(i = 0; i < 16; i++){
        localuser_name[i] = inpbuf[i];
    }
    wprintw(console, "\nYour username is: %s\n", localuser_name);
    wrefresh(console);
    move(ay, 0);
    wclrtoeol(textfield);
    wprintw(textfield, "filler text here");
    curses_cmdprompt();
}

void* curses_viewconfig(){
    curses_cmdprompt();
}

void* connectmenu(){
    wprintw(console, "\nAvailable connection targets:\n\n");
    wprintw(console, "1) Peer-to-peer\n");
    wprintw(console, "2) Server");
    wattrset(console, COLOR_PAIR(1));
    wprintw(console, "(unimplemented)\n");
    wrefresh(console);
    wclrtoeol(textfield);
    wprintw(textfield, "Connection target type: ");
    move(ay, 24);
    wrefresh(textfield);
    refresh();
    wgetnstr(textfield, inpbuf, 32);
    if(strncmp(inpbuf, "1", 32) == 0){
        //connection type is p2p
        clearinpbuf();
        wmove(textfield, 0, 0);
        wclrtoeol(textfield);
        wprintw(textfield, "Are you hosting? [y/N]: ");
        wgetch(textfield);
        curses_cmdprompt();

        /* When connection is setup switch to chat mode,
        command input can be switched back to with some command */
    }else if(strncmp(inpbuf, "2", 32) == 0){
        //connnection type is c2s
        curses_cmdprompt();
    }else{
        wattrset(console, COLOR_PAIR(1));
        wprintw(console, "Invalid target type. ");
        wattrset(console, COLOR_PAIR(7));
        wprintw(console, "Please try again.\n");
        wrefresh(console);
        curses_cmdprompt();
    }
}

void* curses_chwin(){
    curses_cmdprompt();
}

void* curses_exit_confirmation(){
    wclrtoeol(textfield);
    wprintw(textfield, "Are you sure you would like to exit? [y/N]: ");
    wrefresh(textfield);
    move(ay, 44);
    char ec;
    ec = getch();
    if(ec == 'y' || ec == 'Y'){
        curses_end();
    }else{
    curses_cmdprompt();
    }
}

void* curses_end(){
    clear();
    refresh();
    echo();
    endwin();
    exitprompt();
}
