#include <iostream>
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

//i wanna put some debugging functions here but i am an uncreative slimeball so i have zero clue what exactly
//fuck it i'll just make it a wrapper to call partially implemented shit

void DEBUG_netsrv_test(){
    thread p2pserver(TEST_netinit_server);
    p2pserver.join();
}

void DEBUG_netcli_test(){
    thread p2pclient(TEST_netinit_client);
    p2pclient.join();
}
