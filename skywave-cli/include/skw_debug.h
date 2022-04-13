#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <pthread.h>
#include <curses.h>

void* DEBUG_notifytest(){
    wprintw(console, "DEBUG: Send test notification.\n");
    wrefresh(console);
    system("notify-send 'Hello world!' 'This is an example notification.' --icon=dialog-information");
    curses_cmdprompt();
}

void* DEBUG_curses_vartest(){
    clear();
    //mvprintw();
}

void* DEBUG_terminfo(){
    wprintw(console, "displaymode = %d\nay = %d\nax = %d\nmax_y = %d\nmax_x = %d\n", displaymode, ay, ax, max_y, max_x);
    wrefresh(console);
    curses_cmdprompt();
}

void* DEBUG_keytest_echo(){
    curses_cmdprompt();
}

void* DEBUG_keytest_noecho(){
   curses_cmdprompt();
}
