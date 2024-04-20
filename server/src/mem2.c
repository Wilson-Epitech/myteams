/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** mem2
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "libs/arr.h"
#include "libs/def.h"
#include "libs/mem.h"
#include "libs/str.h"
#include "server.h"

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
    user->uuid = generate_uuid();
    user->loged = true;
    arr_pushback(&(server->users), user);
    return user;
}

void team_free(void *ptr)
{
    team_t *team = ptr;

    if (team == NULL) {
        return;
    }
    destroy(team->name);
    destroy(team->description);
    destroy(team->channels);
    ptr_free(team->subscribers);
    destroy(team->uuid);
    ptr_free(ptr);
}

team_t *create_team(
    server_t *server, user_t *creator, char *name, char *description)
{
    team_t *team;

    for (size_t i = 0; server->teams[i]; i++) {
        if (strcmp(server->teams[i]->name, name) == 0) {
            return NULL;
        }
    }
    team = alloc(sizeof(team_t), team_free);
    if (team == NULL) {
        PERR_NORET("Couldn't Alloc Team");
        return NULL;
    }
    team->name = strcreate(name);
    team->description = strcreate(description);
    team->channels = arr_alloc(1);
    team->creator = creator;
    team->subscribers = arr_alloc(1);
    team->uuid = generate_uuid();
    return team;
}
