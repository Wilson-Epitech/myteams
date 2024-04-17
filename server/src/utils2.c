/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** user
*/

#include <stdio.h>
#include <string.h>

#include "libs/arr.h"
#include "libs/mem.h"
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

dm_t **find_dms(dm_t **dms, user_t *sender, user_t *receiver)
{
    dm_t **found = arr_alloc(1);

    for (size_t i = 0; dms[i]; i++) {
        if ((strcmp(dms[i]->sender->uuid, sender->uuid) == 0 &&
                strcmp(dms[i]->receiver->uuid, receiver->uuid) == 0) ||
            (strcmp(dms[i]->sender->uuid, receiver->uuid) == 0 &&
                strcmp(dms[i]->receiver->uuid, sender->uuid) == 0)) {
            arr_pushback(&found, dms[i]);
        }
    }
    return found;
}
