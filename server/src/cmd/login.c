/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** login
*/

#include <stdio.h>
#include <string.h>

#include "client.h"
#include "cmd.h"
#include "error.h"
#include "libs/arr.h"
#include "libs/str.h"
#include "server.h"

static const char success_format[] = "002 %s logged in, proceed.\n";

void login(server_t *server, client_t *client, char **argv, size_t argc)
{
    if (argc != 1) {
        reply(client->fd, _ERROR_101);
        return;
    }
    if (client->username != NULL) {
        reply(client->fd, _ERROR_103);
        return;
    }
    client->username = strcreate(*argv);
    for (size_t i = 0; server->usernames[i]; i++) {
        if (strcmp(server->usernames[i], client->username) == 0) {
            dprintf(client->fd, success_format, client->username);
            return;
        }
    }
    arr_pushback(&(server->usernames), strcreate(client->username));
    dprintf(client->fd, success_format, client->username);
}
