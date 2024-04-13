/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** user
*/

#include <stdio.h>
#include <string.h>

#include "cmd.h"
#include "libs/mem.h"
#include "libs/str.h"
#include "reply.h"
#include "server.h"

static void display_user(server_t *server, client_t *client, char *arg)
{
    user_t **users = server->users;
    SMART char *uuid = strncreate(arg + 1, strlen(arg) - 2);

    while (*users) {
        if (strcmp((*users)->uuid, uuid) == 0) {
            break;
        }
        users++;
    }
    if (*users) {
        dprintf(client->fd, _008_, (*users)->name, (*users)->uuid,
            (*users)->loged);
    } else {
        dprintf(client->fd, _105_);
    }
}

void user(server_t *server, client_t *client, char **argv, size_t argc)
{
    (void)argv;
    if (argc != 1) {
        dprintf(client->fd, _101_);
        return;
    }
    if (client->user && client->user->loged) {
        display_user(server, client, *argv);
    } else {
        dprintf(client->fd, _104_);
    }
}
