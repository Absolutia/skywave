#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "protocol.h"

/**
 * USERDB FUNCTIONS
 * ...
 */

struct user_profile *init_user(){
    struct user_profile *new_user = malloc(sizeof(struct user_profile));
    memset(new_user, 0, sizeof(struct user_profile));
    return new_user;
}

struct user_profile *load_profile(uint32_t uid){
    FILE *userdb = fopen("users.db", "r");
    fseek(userdb, (sizeof(struct user_profile) * uid), SEEK_SET);
    fclose(userdb);
    return userdb;
}
