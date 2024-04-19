/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** utils3
*/

#include <stdio.h>
#include <string.h>

#include "server.h"

client_t *find_client(client_t **clients, user_t *user)
{
    for (size_t i = 0; clients[i]; i++) {
        if (clients[i]->user == user) {
            return clients[i];
        }
    }
    return NULL;
}
