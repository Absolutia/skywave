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
        printw("Create file pointer pFile.");
        FILE *pFile;
        printw("Open file conf.conf.");
        pFile = fopen("conf.conf","w");
        fprintf(pFile, "%d[%-1.24s]", strlen(localuser_name), localuser_name);
        fclose(pFile);
        curses_prompt();
    }
}
