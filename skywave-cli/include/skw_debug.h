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
//i wanna put some debugging functions here but i am an uncreative slimeball so i have zero clue what exactly
//fuck it i'll just make it a wrapper to call partially implemented shit

void* DEBUG_notifytest(){
    wprintw(console, "DEBUG: Send test notification.\n");
    wrefresh(console);
    system("notify-send 'Hello world!' 'This is an example notification.' --icon=dialog-information");
    curses_prompt();
}

void* DEBUG_netsrv_test(){
    pthread_t netsrv;
    pthread_create(&netsrv, NULL, TEST_netinit_server, NULL);
    pthread_join(netsrv, NULL);
}

void* DEBUG_netcli_test(){
    pthread_t netcli;
    pthread_create(&netcli, NULL, TEST_netinit_client, NULL);
    pthread_join(netcli, NULL);
}
