#include <stdint.h>
#include <stdbool.h>

extern char buffer[1024];
extern char actmessage[32];

struct user_profile{
    //personal information
    char first_name[15];
    char middle_name[15];
    char surname_name[15];
    char name_suffix[15];
    uint8_t sex;
    char personal_pronoun[3];
    char secondary_pronoun[3];
    char ownership_pronoun[3];
    time_t birthdate;
    
    //special information
    char custom_status[15];
    char motto[63];
    char bio[255];
    
    //account metadata
    char username[31];
    uint16_t dupe_tag;
    uint16_t reputation;
    uint8_t permission_level;
    uint8_t account_grade;
    time_t account_creation;
    uint8_t account_tenure;
    
    //NOTE: stop rendering a profile value and move to the next when we hit NULL
};

struct user_meta{
    uint32_t uid;
    uint8_t status;
    uint8_t options;
    struct user_profile *profile;
};

struct login_session{
    uint32_t sessionfd; //network socket associated with the session
    struct user_meta *user;
};

struct skywave_message{
    uint64_t messageheader;
    /**
     * messageheader:
     * MMRRRRRR PPPPPPPP PPPPPPP ...
     * 
     * message type(MM):
     * 00:  ignoreme
     * 01:  request
     * 10:  response
     * 11:  broadcast
     * 
     * request/response/broadcast type (RRRRRR)
     * requests--
     * 000000:    none
     * 000001:    register account, (char[])username (char[])password
     * 000010:    login, (char[])username (char[])password
     * 000011:    logout
     * 000100:    keepalive/ping
     * 000101:    opencomm, (uint32_t)uid (uint8_t)type
     * 000110:    login_uid, (uint32_t)uid (char[])password
     * 001000:    login_uid_hash, (uint32_t)uid (char[])password_hash_sha256
     * 
     * responses--
     * 000000:    unsupported
     * 000001:    failure
     * 000010:    success
     * 000011:    uid, (uint32_t)uid
     * 
     * broadcast--
     * 000000:    protocol version
     * 000001:    userstatus
     * 
     * msgtype is followed immediately by the parameters of the message (represented by the P bits)
     */
    uint64_t messagefooter; //footer is optional, not def. right now
};
