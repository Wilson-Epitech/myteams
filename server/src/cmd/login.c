/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** login
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../libs/myteams/logging_server.h"
#include "cmd.h"
#include "libs/def.h"
#include "libs/mem.h"
#include "libs/str.h"
#include "reply.h"
#include "server.h"

static int try_load_user(server_t *server, client_t *client, char *username)
{
    user_t *user = find_user(server, username);

    if (user == NULL) {
        return FAILURE;
    }
    if (user->loged) {
        dprintf(client->fd, _104_);
    } else {
        client->user = user;
        user->loged = true;
    }
    return SUCCESS;
}

void login(server_t *server, client_t *client, char **argv, size_t argc)
{
    SMART char *username = strncreate((*argv) + 1, strlen(*argv) - 2);

    if (argc != 1 || client->user != NULL) {
        dprintf(client->fd, argc != 1 ? _101_ : _104_);
        return;
    }
    if (strlen(username) > MAX_NAME_LENGTH) {
        dprintf(client->fd, _102_);
        return;
    }
    if (try_load_user(server, client, username) == FAILURE) {
        create_user(server, username);
        client->user = find_user(server, username);
        server_event_user_created(client->user->uuid, client->user->name);
        dprintf(client->fd, _001_, client->user->name, client->user->uuid);
    }
    server_event_user_loaded(client->user->uuid, client->user->name);
    server_event_user_logged_in(client->user->uuid);
    dprintf(client->fd, _002_, client->user->name, client->user->uuid);
    dprintf(client->fd, _003_, client->user->name, client->user->uuid);
}
