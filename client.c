#include <assert.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#ifndef __SKW_PROT_H
    #include "protocol.h"
    #define __SKW_PROT_H
#endif

int clientloop(uint8_t flags){

    fprintf(stdout, "[STATUS] Running in client mode\n");
    fprintf(stdout, "[STATUS] Entering clientloop()\n");
	struct sockaddr_in metabindaddr, metapeeraddr, metaconnaddr;
	memset(&metabindaddr, 0, sizeof(metabindaddr));
	memset(&metapeeraddr, 0, sizeof(metapeeraddr));
	memset(&metaconnaddr, 0, sizeof(metaconnaddr));

    errno = 0;
    uint32_t clisockfd = socket(AF_INET, SOCK_STREAM, 6);
    if(!clisockfd){
        perror("Error retrieving socket descriptor");
        return 0;
    }else{
        fprintf(stdout, "[STATUS] Socket created\n");
    }

    metaconnaddr.sin_family = AF_INET;
    metaconnaddr.sin_port = 50000;
    inet_aton("127.0.0.1", &metaconnaddr.sin_addr);

    errno = 0;
    if(connect(clisockfd, (struct sockaddr *)&metaconnaddr, sizeof(metaconnaddr)) == -1){
        perror("Error connecting to server");
        close(clisockfd);
        return 0;
    }else{
        fprintf(stdout, "[STATUS] Connected to server\n");
        char buffer[1024];
        errno = 0;
        int recvv = recv(clisockfd, buffer, sizeof(buffer), MSG_WAITALL);
        errno = 0;
        fprintf(stdout, "%d bytes recieved\n", recvv);
        if(recvv == 0){
            fprintf(stdout, "No data\n");
        }
        fprintf(stdout, "%s", buffer);
    }
    return INT_MAX;
}
