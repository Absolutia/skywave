//variables

static const char s[2] = " ";
char *token;

static const char port[] = "POSIX"; //is this an accurate descriptor? it runs under linux and BSD, i've checked

static const char majphase[] = "Alpha"; //alpha: so we're implementing features
static const char minphase[] = "M3"; //in milestone 3
static const int revision = 195;
static const int minver = 0;
static const int majver = 0;

static const char month[] = "February";
static const int day = 0;
static const int year = 2022;

static const bool autoload = true; //enable conf autoload
static const bool dbg = true; //signifies that this build is for debugging purposes
static const bool expui = false; //<--DEPRECATE THIS, EXPUI IS NOW DEFAULT

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

pthread_t notify;
pthread_t p2p_netsrv;
pthread_t p2p_netcli;
pthread_t fileio;

//declare ncurses windows, as global vars
/** DO NOT CHANGE THESE */
WINDOW *stdscr;
WINDOW *versionbanner;
//WINDOW *connectbanner; //pos is 1y below versionbanner
WINDOW *console;
//WINDOW * //need a good name for this one
WINDOW *textfield;

/** functions, sorted by file */
//main
void clearinpbuf();

//skw_cursesui
void* curses_init(); // curses ui
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

void* curses_configure(); //integrated configurator
void* curses_viewconfig(); //display configuration
void* saveconfig(); //save configuration
void* loadconfig(); //load configuration
void* connectmenu();

//void* curses_check_if_finished(); //check if all secondary threads are finished before exiting <- deprecate because all threads terminate on process exit

void* exitprompt();

//skw_fileio
void* wconfig();

//skw_network
void* p2p_init();
void* net_p2p_server();
void* net_p2p_client();
void* TEST_netinit_server();
void* TEST_netinit_client();

//skw_debug
void* DEBUG_notifytest();
