/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** login
*/

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../libs/myteams/logging_server.h"
#include "cmd.h"
#include "libs/arr.h"
#include "libs/def.h"
#include "reply.h"
#include "server.h"

static void event_login(void *_client, va_list ap)
{
    client_t *client = _client;
    client_t *event = va_arg(ap, client_t *);

    dprintf(client->fd, _003_, event->user->name, event->user->uuid);
}

static void show_logout(client_t *client)
{
    if (client->user) {
        client->user->loged = false;
        dprintf(client->fd, _004_, client->user->name, client->user->uuid);
        server_event_user_logged_out(client->user->uuid);
    }
}

static int try_load_user(server_t *server, client_t *client, char *username)
{
    user_t *user = find_user(server, username);

    if (user == NULL) {
        create_user(server, username);
        client->user = find_user(server, username);
        server_event_user_created(client->user->uuid, client->user->name);
        dprintf(client->fd, _001_, client->user->name, client->user->uuid);
        return SUCCESS;
    }
    if (user->loged) {
        dprintf(client->fd, _104_);
    } else {
        show_logout(client);
        client->user = user;
        client->user->loged = true;
        server_event_user_loaded(client->user->uuid, client->user->name);
        dprintf(client->fd, _002_, client->user->name, client->user->uuid);
    }
    return (user == client->user) ? SUCCESS : FAILURE;
}

void login(server_t *server, client_t *client, char **argv, size_t argc)
{
    char *username = *argv;

    if (argc != 1) {
        dprintf(client->fd, _101_);
        return;
    }
    if (strlen(username) > MAX_NAME_LENGTH) {
        dprintf(client->fd, _102_);
        return;
    }
    if (try_load_user(server, client, username) == FAILURE) {
        return;
    }
    server_event_user_logged_in(client->user->uuid);
    arr_foreach_arg(server->clients, event_login, client);
}
