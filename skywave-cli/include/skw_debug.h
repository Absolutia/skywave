#include <stdio.h>
#include <stdlib.h>
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

void* DEBUG_notifytest(){
    wprintw(console, "DEBUG: Send test notification.\n");
    wrefresh(console);
    system("notify-send 'Hello world!' 'This is an example notification.' --icon=dialog-information");
    curses_prompt();
}
