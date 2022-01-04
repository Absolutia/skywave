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

void loadconfig(){

    if(expui == true){
        return;
    }else{
        curses_prompt();
    }
}

void saveconfig(){
    if(expui == true){
        return;
    }else{
        if(strlen(localuser_name) == NULL || strlen(localuser_name) == 0){
            printw("Fatal error: localuser_name is undefined or of zero length.\n");
            curses_prompt();
        }

        printw("Create file pointer pFile.\n");
        FILE *pFile;
        printw("Open file conf.conf.\n");
        pFile = fopen("conf.conf","w");
        printw("Write data: strlen(localuser_name): %d, localusername: [%-1.24s]\n", strlen(localuser_name), localuser_name);
        fprintf(pFile, "%d[%-1.24s]", strlen(localuser_name), localuser_name);
        fclose(pFile);
        curses_prompt();
    }
}
