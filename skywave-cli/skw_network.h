#include <stdio.h>
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

//final p2p implementations go here
void* p2p_init(){
    //establish full-duplex p2p connection with target(s)
    //NEEDS MULTITHREADING
    /*
    net_p2p_server();
    net_p2p_client();
    */
    return 0;
}

void* net_p2p_server(){
    //serverlol
    return 0;
}

void* net_p2p_client(){
    //clientlol
    return 0;
}

void* TEST_netinit_server(){
    //literally some example code i copy-pasted for testing purposes
    //turning these into netcode prototypes
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    netstate = 1;
    wprintw(console, "NET DBG: socket retrieve done\n");
    wrefresh(console);

    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendbuf, '0', sizeof(sendbuf));
    netstate = 2;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(65000);
    netstate = 3;

    bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));
    netstate = 4;

    if(listen(listenfd, 10) == -1){
        printw("Failed to listen\n");
        lasterror = -1;
        netstate = 0;
    }

    while(1){
        wclear(connectbanner);
        wattrset(connectbanner, COLOR_PAIR(2));
        wprintw(connectbanner, "Now Hosting");
        wattrset(connectbanner, COLOR_PAIR(7));
        wprintw(connectbanner, " | ");
        wprintw(connectbanner, "%d active users", activeusers);
        wprintw(connectbanner, " | ");
        wprintw(connectbanner, "Console");
        wrefresh(connectbanner);
        move(ay, 5);
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
        netstate = 5;

        strcpy(sendbuf, "TEST MESSAGE\n");
        write(connfd, sendbuf, strlen(sendbuf));

        close(connfd);
        netstate = 0;
        sleep(1);
    }

    return 0;
}

void* TEST_netinit_client(){
    //ditto my above comment for netinit_server()
    memset(recvbuf, '0', sizeof(recvbuf));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0){
        printw("\n Error: could not create socket\n");
        lasterror = -1;
        netstate = 0;
    }else{
        netstate = 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(65000);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    netstate = 2;

    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))< 0){
        printw("\nError: connection failed\n");
        lasterror = -1;
        netstate = 0;
    }

    while(1){
        nn = read(sockfd, recvbuf, sizeof(recvbuf)-1);
        if(fputs(recvbuf, stdout) == EOF){
            printw("\nFATAL ERROR: unspecified fputs() failure\n");
            close(sockfd);
            lasterror = -1;
            netstate = 0;
        }else if(nn < 0){
            printw("\nFATAL ERROR: unspecified fputs() failure\n");
            close(sockfd);
            lasterror = -1;
            netstate = 0;
        }
        close(sockfd);
    }

    /*while((nn = read(sockfd, recvbuf, sizeof(recvbuf)-1)) > 0){
        recvbuf[nn] = 0;
        if(fputs(recvbuf, stdout) == EOF){
            printw("\nError: fputs error\n");;
        }

        if(nn < 0){
            printw("\n Read Error \n");
        }
    }*/

    return 0;
}
