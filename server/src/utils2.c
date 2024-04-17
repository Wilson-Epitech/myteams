/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** user
*/

#include <string.h>

#include "server.h"

user_t *find_user(server_t *server, char *username)
{
    user_t **users = server->users;

    for (size_t i = 0; users[i]; i++) {
        if (strcmp(users[i]->name, username) == 0) {
            return users[i];
        }
    }
    return NULL;
}

user_t *find_user_by_uuid(server_t *server, char *uuid)
{
    user_t **users = server->users;

    for (size_t i = 0; users[i]; i++) {
        if (strcmp(users[i]->uuid, uuid) == 0) {
            return users[i];
        }
    }
    return NULL;
}

team_t *find_team_by_name(team_t **teams, char *name)
{
    while (*teams) {
        if (strcmp((*teams)->name, name) == 0) {
            return *teams;
        }
        teams++;
    }
    return NULL;
}

// dm_t **find_dms(dm_t **dms, user_t *user_1, user_t *user_2)
// {
//     dm_t **dms = server->dms;

//     for (size_t i = 0; dms[i]; i++) {
//         if (strcmp(dms[i]->uuid_1, uuid_1) == 0 ||) {
//             return users[i];
//         }
//     }
//     return NULL;
// }
