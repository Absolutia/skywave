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

struct connection_descriptor{
    time_t login_time;
    uint32_t sockfd;
    struct sockaddr_in serv_sockaddr;
    struct sockaddr_in cli_sockaddr;
    struct user_meta *user_meta;
};

int serverloop(uint8_t flags){
    //Setup code
    fprintf(stdout, "[STATUS] Entering serverloop()\n");
    fprintf(stdout, "[STATUS] Running in server mode\n");
	struct sockaddr_in metabindaddr = {0};
    struct sockaddr_in metapeeraddr = {0};
    struct sockaddr_in metaconnaddr = {0};

    errno = 0;
    uint32_t listensockfd = socket(AF_INET, SOCK_STREAM, 6); //6 = TCP
    if(!listensockfd){
        perror("Error retrieving socket descriptor");
        return 0;
    }else{
        fprintf(stdout, "[STATUS] Socket bound\n");
    }

    metabindaddr.sin_family = AF_INET;
    metabindaddr.sin_port = 50000;
    metabindaddr.sin_addr.s_addr = INADDR_ANY;

    errno = 0;
    if(bind(listensockfd, (struct sockaddr *)&metabindaddr, sizeof(struct sockaddr_in)) == -1){
        perror("Error binding socket to address");
        close(listensockfd);
        return 0;
    }else{
        fprintf(stdout, "[STATUS] Bound interface to socket\n");
    }

    errno = 0;
    if(setsockopt(listensockfd, SOL_SOCKET, SO_REUSEADDR, &listensockfd, sizeof(int)) == -1){
        perror("setsockopt()");
    }

    errno = 0;
    if(listen(listensockfd, 1) == -1){
        perror("Error listening on socket");
        close(listensockfd);
        return 0;
    }else{
        fprintf(stdout, "[STATUS] Listening on socket\n");

        errno = 0;
        uint32_t clisock;
        while(true){

            errno = 0;
            clisock = accept(listensockfd, NULL, NULL);
            if(clisock != -1){
                errno = 0;
                struct sockaddr_in metapeeraddr = {0};
		
		struct connection_descriptor temp = {0};
			
		socklen_t sl = sizeof(temp.cli_sockaddr);
                if(getpeername(clisock, (struct sockaddr *)&temp.cli_sockaddr, &sl) == -1){
                    perror("getpeername()");
                }
                fprintf(stdout, "Got connection from %s\n", inet_ntoa(metapeeraddr.sin_addr));

                memset(buffer, 0, sizeof(buffer));
                memcpy(buffer, actmessage, sizeof(actmessage));

                errno = 0;
                int sendv = send(clisock, buffer, sizeof(buffer), 0);
                if(sendv == -1){
                    perror("Error writing to socket");
                }else if(sendv == 0){
                    fprintf(stdout, "Null socket\n");
                    return 0;
                }

                fprintf(stdout, "%d bytes transmitted\n", sendv);
            }else{
                perror("Error accepting connection");
                return 0;
            }
        }
    }
}
