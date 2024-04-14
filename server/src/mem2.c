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

char *generate_uuid(server_t *server)
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

void create_user(server_t *server, char *name)
{
    user_t *user = alloc(sizeof(user_t), user_free);

    if (user == NULL) {
        PERR_NORET("Couldn't Alloc User");
        return;
    }
    user->name = strcreate(name);
    user->uuid = generate_uuid(server);
    user->loged = true;
    arr_pushback(&(server->users), user);
}

void team_free(void *ptr)
{
    team_t *team = ptr;

    if (team == NULL) {
        return;
    }
    destroy(team->name);
    destroy(team->description);
    destroy(team->channel);
    destroy(team->subscribers);
    destroy(team->uuid);
    ptr_free(ptr);
}

void create_team(
    server_t *server, user_t *creator, char *name, char *description)
{
    team_t *team = alloc(sizeof(team_t), team_free);

    if (team == NULL) {
        PERR_NORET("Couldn't Alloc Team");
        return;
    }
    team->name = strcreate(name);
    team->description = strcreate(description);
    team->channel = arr_alloc(1);
    team->creator = creator;
    team->subscribers = arr_alloc(1);
    team->uuid = generate_uuid(server);
}
