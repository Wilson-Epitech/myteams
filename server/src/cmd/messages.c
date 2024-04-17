/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** logout
*/

#include <stdbool.h>
#include <stdio.h>

#include "cmd.h"
#include "libs/mem.h"
#include "libs/str.h"
#include "reply.h"
#include "server.h"

static void show_messages(server_t *server, client_t *client, user_t *other)
{
    dm_t **dms = find_dms(server->dms, client->user, other);
    SMART char *data = strcreate("");

    for (size_t i = 0; dms[i]; i++) {
        stradd_s(&data, "[");
        stradd_s(&data, dms[i]->sender->name);
        stradd_s(&data, "] [");
        stradd_s(&data, dms[i]->message);
        stradd_s(&data, "] ");
    }
    ptr_free(dms);
    dprintf(client->fd, _034_, data);
}

void messages(server_t *server, client_t *client, char **argv, size_t argc)
{
    user_t *other;

    if (!client->user) {
        dprintf(client->fd, _104_);
        return;
    }
    if (argc != 1) {
        dprintf(client->fd, _101_);
        return;
    }
    other = find_user_by_uuid(server, *argv);
    if (!other) {
        dprintf(client->fd, _105_);
        return;
    }
    show_messages(server, client, other);
}
