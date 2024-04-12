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
        server_event_user_loaded(user->uuid, user->name);
        dprintf(client->fd, _002_, user->name, user->uuid);
    }
    return SUCCESS;
}

/*
1 argument
error:
argc is not 1
user already set
user already logged

success
user created | loaded
user logs in
*/
void login(server_t *server, client_t *client, char **argv, size_t argc)
{
    SMART char *username = strncreate((*argv) + 1, strlen(*argv) - 2);

    if (argc != 1) {
        dprintf(client->fd, _101_);
        return;
    }
    if (client->user != NULL) {
        dprintf(client->fd, _104_);
        return;
    }
    if (try_load_user(server, client, username) == FAILURE) {
        save_user(server, username);
        client->user = find_user(server, username);
        dprintf(client->fd, _001_, client->user->name, client->user->uuid);
        dprintf(client->fd, _002_, client->user->name, client->user->uuid);
    }
}
