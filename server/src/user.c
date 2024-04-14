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
