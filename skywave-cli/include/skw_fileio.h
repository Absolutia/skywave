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

void wconfig(){
    FILE *config;

    config = fopen("config.ini", "w");
    fprintf("%s %s %s %s");
    fclose(config);
}
