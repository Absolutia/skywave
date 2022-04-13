#include <stdint.h>
//variables

static const char s[2] = " ";
char *token;

static const char port[] = "POSIX"; //is this an accurate descriptor? it runs under linux and BSD, i've checked
//known good OSes (will compile and run w/o modification):
//	Arch Linux	[AMD64]
//	FreeBSD		[AMD64]
//	Raspbian	[ARM11]

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

//init, status & thread sync variables
unsigned short runstatus = 0;
bool oobe = true;
bool t_init = true; //deprecated
bool t_crsrdy = false;

int ecode = 0; //error code. default is 0, meaning no error.
bool csupport = false;
int fsupport = 0;

char contarget = '0'; //connection target, specified by 8-bit word
//indexes
int i = 0;
int j = 0;
int n = 0;

int w = 0;
int x = 0;
int y = 0;
int z = 0;

//window size?
int displaymode = 0;
int ay = 0;
int ax = 0;
int max_y = 0;
int max_x = 0; //currently subject to revision

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

int netstate = 0;
int lasterror = 0;

int activeusers = 0;

unsigned short localuser_id = 0; //initialize to zero, do not use for now
unsigned short localuser_roleid = 0; //initialize to zero, do not use for now
int localuser_color = 7;
char localuser_name[24];
char localuser_nick[24];
/*char localuser_password[1024];*/ //i'm not sure how to use this yet, DO NOT USE

pthread_t notify, p2p_netsrv, p2p_netcli, fileio;
int iret1, iret2, iret3, iret4;

//variables for strtok()
    //delimiters for packet and command processing
const char delim_space[2] = " ";
const char delim_openpar[2] = "(";
const char delim_closepar[2] = ")";
const char delim_openbrak[2] = "[";
const char delim_closebrak[2] = "]";
const char delim_opencurl[2] = "{";
const char delim_closecurl[2] = "}";
const char delim_lthan[2] = "<";
const char delim_gthan[2] = ">";
const char delim_fslash[2] = "/";
const char demil_bslash[2] = "\\"; //i hope this one works
const char delim_quest[2] = "?";
const char delim_excl[2] = "!";
const char delim_at[2] = "@";
const char delim_hash[2] = "#";
const char delim_cash[2] = "$";
const char delim_percent[2] = "%";
const char delim_carot[2] = "^";
const char delim_ampersand[2] = "&";
const char delim_asterisk[2] = "*";

//declare ncurses windows, as global vars
/** DO NOT CHANGE THESE */
WINDOW *stdscr;
WINDOW *versionbanner;
WINDOW *connectbanner; //pos is 1y below versionbanner
WINDOW *console;
WINDOW *channel1; //overlay channels on top of the console
WINDOW *channel2;
WINDOW *channel3;
WINDOW *channel4;
WINDOW *textfield;

/** functions, sorted by file */
//main
void clearinpbuf();

//skw_cursesui
void* curses_init(); // curses ui
void* curses_printbanner(); //print banner
void* curses_printconnect(); //print connection banner
void* curses_oobe(); //out of box experience
void* curses_keyprompt();
void* curses_cmdprompt(); //prompt for input
void* curses_dbgprompt();
void* curses_cmdparse(); //parse commands
void* curses_chwin(); //change window
void* curses_test(); //test command
void* curses_cmdhelp(); //display command help
void* curses_dbghelp();
void* curses_skw_version(); //version information
void* curses_changelog(); //change log
void* curses_credits(); //credits
void* curses_exit_confirmation(); //exit confirmation prompt
void* curses_end(); //end curses session

void* curses_configure(); //integrated configurator
void* curses_viewconfig(); //display configuration
void* saveconfig(); //save configuration
void* loadconfig(); //load configuration
void* connectmenu(); //interactive connection menu

//void* curses_check_if_finished(); //check if all secondary threads are finished before exiting <- deprecate because all threads terminate on process exit

void* returnerror();
void* exitprompt();

//skw_fileio
void* wconfig();
void* rconfig();

//skw_network
void* p2p_init();
void* net_p2p_server();
void* net_p2p_client();
void* TEST_netinit_server();
void* TEST_netinit_client();

//skw_debug
void* DEBUG_notifytest();
void* DEBUG_terminfo();
void* DEBUG_keytest_echo();
void* DEBUG_keytest_noecho();
