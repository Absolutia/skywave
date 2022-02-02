//variables

static const char s[2] = " ";
char *token;

static const char port[] = "POSIX"; //is this an accurate descriptor? it runs under linux and BSD, i've checked

static const char majphase[] = "Alpha"; //alpha: so we're implementing features
static const char minphase[] = "M2"; //in milestone 2
static const int revision = 190;
static const int minver = 0;
static const int majver = 0;

static const char month[] = "December";
static const int day = 9;
static const int year = 2021;

static const bool autoload = true; //enable conf autoload
static const bool dbg = true; //signifies that this build is for debugging purposes
static const bool expui = true; //enable experimental ui

//init, status & thread sync variables
unsigned short runstatus = 0;
bool t_init = true;
bool t_crsrdy = false;

char contarget = '0'; //connection target, specified by 8-bit word
int i = 0; //index i
int j = 0; //index j
int n = 0; //index n

//these variables should be used for char-by-char terminal painting
int cy = 0;
int cx = 0;
int oy = 0;
int ox = 0;

//window size?
int ay = 0;
int ax = 0;

char inpbuf[32]; //input buffer
//will need buffering logic eventually

//network variables
int listenfd = 0;
int connfd = 0;
int sockfd = 0;

int nn = 0;

struct sockaddr_in serv_addr;

char sendbuf[1025];
int numrv;

char recvbuf[1024];

int lasterror;

unsigned short localuser_id = 0; //initialize to zero, do not use for now
unsigned short localuser_roleid = 0; //initialize to zero, do not use for now
char localuser_name[24];
char localuser_nick[24];
/*char localuser_password[1024];*/ //i'm not sure how to use this yet, DO NOT USE

/*
class remoteuser{
    unsigned short remoteuser_name[24];
    unsigned short remoteuser_nick[24];
    char p2p_handshake_passphrase[32];
};

class peer{
    unsigned short index;
    char peername[32];
    char ipv4[16];
};*/

/*void objtest(){
    localuser bob;
    bob.id = 1234;
    bob.id = bob.id + 2;
    localuser alice[5];
    alice[1].id = 1234;
    alice[1].id = alice[1].id + 2;
}*/ //we'll save object orientation for another time, c++ is getting in the way
    //scratch that, found an ncurses solution for this problem, might choose to bring c++ back for EZ threading

//declare ncurses windows, as global vars
/** DO NOT CHANGE THIS */
WINDOW *stdscr;
WINDOW *banner;
WINDOW *console;
WINDOW *textfield;

/** functions, sorted by file */
//main
void clearinpbuf();

//skw_cursesui
void* curses_init(); //experimental curses ui
void* curses_printbanner(); //print banner
void* curses_prompt(); //prompt for input
void* curses_parse(); //parse commands
void* curses_test(); //test command
void* curses_help(); //display help
void* curses_skw_version(); //version information
void* curses_changelog(); //change log
void* curses_credits(); //credits
void* curses_exit_confirmation(); //exit confirmation prompt
void* curses_end(); //end curses session

/** void* curses_init(); //initialize curses
void* curses_splash(); //initial splash
void* curses_prompt(); //command prompt
void* curses_parse(); //parse commands
void* curses_clear(); //clear screen
void* curses_help(); //command list
void* curses_skw_version(); //version string
void* curses_changelog(); //show change log
void* curses_credits(); //show credits */

void* curses_configure(); //configurator
void* curses_configuration(); //display configuration
void* saveconfig();
void* loadconfig();

//void* curses_check_if_finished(); //check if all secondary threads are finished before exiting

void* exitprompt();

//skw_cursesui_experimental
/** Deprecated */

//skw_fileio
void* wconfig();

//skw_network
void* TEST_netinit_server();
void* TEST_netinit_client();

//skw_debug
void* DEBUG_notifytest();
void* DEBUG_netsrv_test();
void* DEBUG_netcli_test();
