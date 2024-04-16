/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** utils
*/

#include <stdio.h>
#include <string.h>

#include "libs/mem.h"
#include "libs/str.h"
#include "server.h"

char *generate_uuid(server_t *server)
{
    char *uuid = ptr_alloc(sizeof(char) * (36 + 1));

    sprintf(uuid, "%036ld", server->uuid);
    server->uuid += 1;
    return uuid;
}

void remove_quote(char **arr)
{
    char *tmp;

    while (*arr) {
        tmp = *arr;
        arr[0] = strncreate((*arr) + 1, strlen(*arr) - 2);
        destroy(tmp);
        arr++;
    }
}
