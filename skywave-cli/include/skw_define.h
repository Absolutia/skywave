//variables
using namespace std;

static const char port[] = "POSIX"; //is this an accurate descriptor? it runs under linux and BSD, i've checked

static const char majphase[] = "Alpha"; //alpha: so we're implementing features
static const char minphase[] = "M2"; //milestone 2
static const int revision = 160;
static const int minver = 0;
static const int majver = 0;

static const char month[] = "December";
static const int day = 9;
static const int year = 2021;

const bool dbg = true; //signifies that this build is for debugging purposes

const bool experimentalui = false; //enable experimental ui

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

//classes, these will mainly be used by server-related stuff
class localuser{
    public:
        int id; //hex, used by servers to distinguish users with the same name
        char name[16]; //actual username
        char nick[32]; //area specific nickname

    private:
        char password[32]; //password, used for server accounts and p2p handshakes
        int roleid;
};

class remoteuser{
    public:
        int id;
        char name[32];
        char nick[32];
        int roleid;
};

class peer{
    public:
        char label[16];
        int ipv4;
        int port;

    private:
        char connection_passphrase[32];
};

class server{
    public:
        char label[16];
        int ipv4; //hex ipv4
        int port; //hex port number

    private:
        char connection_passphrase[32];
};

/*void objtest(){
    localuser bob;
    bob.id = 1234;
    bob.id = bob.id + 2;
    localuser alice[5];
    alice[1].id = 1234;
    alice[1].id = alice[1].id + 2;
}*/


/** functions, sorted by file */
//main
void clearinpbuf();

//skw_cursesui_plain
void curses_init(); //initialize curses
void curses_splash(); //initial splash
void curses_prompt(); //command prompt
void curses_parse(); //parse commands
void curses_clear(); //clear screen
void curses_help(); //command list
void curses_skw_version(); //version string
void curses_changelog(); //show change log
void curses_credits(); //show credits

void curses_configure(); //configuration utility

void curses_check_if_finished(); //check if all secondary threads are finished before exiting
void curses_end(); //end curses sesssion
void curses_exit_confirmation(); // exit confirmation prompt

void exitprompt(); //uhhhh same as above?

//skw_cursesui_experimental
void curses_experimental_init(); //experimental curses ui

//skw_fileio
void wconfig();

//skw_network
void netinit_server();
void netinit_client();

//skw_debug
    //sorry nothing
