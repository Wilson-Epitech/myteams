/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** users
*/

#include <stdio.h>

#include "cmd.h"
#include "libs/mem.h"
#include "libs/str.h"
#include "reply.h"
#include "server.h"

static void display_users(server_t *server, client_t *client)
{
    user_t **users = server->users;
    SMART char *data = strcreate("");

    while (*users) {
        stradd_c(&data, '[');
        stradd_s(&data, (*users)->name);
        stradd_s(&data, "] [");
        stradd_s(&data, (*users)->uuid);
        stradd_s(&data, "] [");
        stradd_c(&data, (*users)->loged ? '1' : '0');
        stradd_s(&data, "] ");
        users++;
    }
    dprintf(client->fd, _007_, data);
}

void users(server_t *server, client_t *client, char **argv, size_t argc)
{
    (void)argv;
    if (argc != 0) {
        dprintf(client->fd, _101_);
        return;
    }
    if (client->user) {
        display_users(server, client);
    } else {
        dprintf(client->fd, _104_);
    }
}
