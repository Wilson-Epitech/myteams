/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** logout
*/

#include <stdio.h>

#include "../libs/myteams/logging_server.h"
#include "cmd.h"
#include "libs/arr.h"
#include "reply.h"
#include "server.h"

void logout(server_t *server, client_t *client, char **argv, size_t argc)
{
    (void)argv;
    if (argc != 0) {
        dprintf(client->fd, _101_);
        return;
    }
    if (client->user) {
        client->user->loged = false;
        dprintf(client->fd, _004_);
        server_event_user_logged_out(client->user->uuid);
    }
    dprintf(client->fd, _005_);
    arr_remove_ptr(server->clients, client);
}
