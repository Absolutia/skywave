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

/*#ifndef __SKW_PROT_H
    #include "protocol.h"
    #define __SKW_PROT_H
#endif*/

char buffer[1024];
char actmessage[] = "Skywave Communicator v0.1\n\0";

uint32_t i;

//int netloop(uint8_t);
int clientloop(uint8_t);
int serverloop(uint8_t);

int main(int argc, char **argv){
/** Command line (argv) format: 
 *  skywave [MODE] [OPTIONS] 
 *
 *  The [MODE] field is required.
 *
 *  Options always begin with a hyphen and are short-form (ie "-h"),
 *  long-form options (ie "--help") are never valid. This is to simplify
 *  parser implementation. */
	if(!getuid()){
		fprintf(stderr, "Refusing to run as root, exiting\n");
		return 0;
	}
	
	fprintf(stdout, "[SYSTEM] ");
	for(i = 0; i <= (argc - 1); i++){
		fprintf(stdout, "%s ", argv[i]);
	}
	fprintf(stdout, "\n");
	fprintf(stdout, "[SYSTEM] Input %d arguments\n", argc);
	
    uint8_t flags = 0;
	for(i = 1; i <= (argc - 1); i++){
		if(strcmp(argv[1], "server") == 0){
			flags = flags | 1; //assert lsb with bitwise OR
		}
	}

	switch(flags){
        case 0:
            clientloop(flags);
            break;
        case 1:
            serverloop(flags);
            break;
    }
	
	/*if(!netloop(flags)){
		fprintf(stdout, "[SYSTEM] Failure starting netcode, exiting\n");
		return 0;
	}*/
	
	return 1;
}
