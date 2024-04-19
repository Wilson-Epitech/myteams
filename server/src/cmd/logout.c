/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** logout
*/

#include <stdbool.h>
#include <stdio.h>

#include "../libs/myteams/logging_server.h"
#include "cmd.h"
#include "libs/arr.h"
#include "reply.h"
#include "server.h"

// static void event_logout(void *_client, va_list ap)
// {
//     client_t *client = _client;
//     client_t *event = va_arg(ap, client_t *);

//     dprintf(client->fd, _004_, event->user->name, event->user->uuid);
// }

void logout(server_t *server, client_t *client, char **argv, size_t argc)
{
    (void)argv;
    (void)argc;
    if (client->user) {
        dprintf(client->fd, _004_, client->user->name, client->user->uuid);
        client->user->loged = false;
        server_event_user_logged_out(client->user->uuid);
    } else {
        dprintf(client->fd, _004_, "", "");
    }
    arr_remove_ptr(server->clients, client, true);
}
// arr_foreach_arg(server->clients, event_logout, client);
// dprintf(client->fd, _005_);
