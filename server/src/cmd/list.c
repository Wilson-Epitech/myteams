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

static void list_replies(client_t *client)
{
    SMART char *data = strcreate("");

    for (reply_t **rep = client->thread_ctx->replies; *rep; rep++) {
        stradd_c(&data, '[');
        stradd_s(&data, (*rep)->body);
        stradd_s(&data, "] , ");
    }
    dprintf(client->fd, _025_, data);
}

static void list_threads(client_t *client)
{
    SMART char *data = strcreate("");

    for (thread_t **th = client->channel_ctx->threads; *th; th++) {
        stradd_c(&data, '[');
        stradd_s(&data, (*th)->title);
        stradd_s(&data, "] about ");
        stradd_c(&data, '[');
        stradd_s(&data, (*th)->message);
        stradd_s(&data, "] , ");
    }
    dprintf(client->fd, _026_, data);
}

static void list_channels(client_t *client)
{
    SMART char *data = strcreate("");

    for (channel_t **ch = client->team_ctx->channels; *ch; ch++) {
        stradd_c(&data, '[');
        stradd_s(&data, (*ch)->uuid);
        stradd_s(&data, "] about ");
        stradd_c(&data, '[');
        stradd_s(&data, (*ch)->name);
        stradd_s(&data, "] about ");
        stradd_c(&data, '[');
        stradd_s(&data, (*ch)->description);
        stradd_s(&data, "] , ");
    }
    dprintf(client->fd, _027_, data);
}

static void list_teams(server_t *server, client_t *client)
{
    SMART char *data = strcreate("");

    for (team_t **teams = server->teams; *teams; teams++) {
        stradd_c(&data, '[');
        stradd_s(&data, (*teams)->uuid);
        stradd_s(&data, "] about ");
        stradd_c(&data, '[');
        stradd_s(&data, (*teams)->name);
        stradd_s(&data, "] about ");
        stradd_c(&data, '[');
        stradd_s(&data, (*teams)->description);
        stradd_s(&data, "] , ");
    }
    dprintf(client->fd, _028_, data);
}

void list(server_t *server, client_t *client, char **argv, size_t argc)
{
    (void)argv;
    if (!client->user) {
        dprintf(client->fd, _104_);
        return;
    }
    if (argc != 0) {
        dprintf(client->fd, _101_);
        return;
    }
    if (client->thread_ctx) {
        list_replies(client);
        return;
    } else if (client->channel_ctx) {
        list_threads(client);
        return;
    }
    if (client->team_ctx) {
        list_channels(client);
    } else
        list_teams(server, client);
}
