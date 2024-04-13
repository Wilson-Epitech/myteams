/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** mem2
*/

#include <stdbool.h>
#include <stdio.h>

#include "libs/arr.h"
#include "libs/def.h"
#include "libs/mem.h"
#include "libs/str.h"
#include "server.h"

static char *generate_uuid(server_t *server)
{
    size_t uuid_nb = arrlen(server->users);
    char *uuid = ptr_alloc(sizeof(char) * (36 + 1));

    sprintf(uuid, "%036ld", uuid_nb);
    return uuid;
}

void user_free(void *ptr)
{
    user_t *user = ptr;

    if (user == NULL) {
        return;
    }
    destroy(user->name);
    destroy(user->uuid);
    ptr_free(ptr);
}

user_t *create_user(server_t *server, char *name)
{
    user_t *user = alloc(sizeof(user_t), user_free);

    if (user == NULL) {
        PERR_NORET("Couldn't Alloc User");
        return NULL;
    }
    user->name = strcreate(name);
    user->uuid = generate_uuid(server);
    user->loged = true;
    arr_pushback(&(server->users), user);
    return user;
}
