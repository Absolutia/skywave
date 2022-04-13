#include <stdio.h>
#include <stdint.h>
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

#include <skw_define.h>
#include <skw_debug.h>

#include <skw_cursesui.h>
#include <skw_fileio.h>
#include <skw_network.h>

void clearinpbuf(){
    memset(inpbuf,0,sizeof(inpbuf));
    return;
}

void* returnerror(){
    switch(ecode){
	case 0:
	printf("DEBUG: %d: No error returned.", ecode);
	break;
	case 1:
	printf("DEBUG: %d: ERROR: Your terminal doesn't support color. You will only get monochrome output.\n", ecode);
	break;
	case 2:
	printf("DEBUG: %d: FATAL: Either your terminal has incomplete or nonexistent support for function keys.\n", ecode);
	break;
	
	default:
	printf("DEBUG: %d: Unknown ecode.\n", ecode);
	break;
    }
    return 0;
}

void* exitprompt(){
    system("clear");
    if(dbg == true){
        returnerror();
	printf("\nThank you for using Skywave!\n");
	system("sleep 3");
	exit(0);
    }else{
    	printf("Thank you for using Skywave!\n");
	system("sleep 3");
	exit(0);
    }
}

int main(int argc, char *argv[])
{
    system("clear");
    //check if a file called "nooobe" is present, and then set oobe = false if it is.
    
    if(autoload == true){
        //loadconfig();
	curses_init();
    }else{
        curses_init();
    }
    /*Got rid of threading code here,
    new threads will be spawned as needed from the curses session.*/
}
