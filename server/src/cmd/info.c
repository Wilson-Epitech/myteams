/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** logout
*/

#include <stdbool.h>
#include <stdio.h>

#include "cmd.h"
#include "reply.h"
#include "server.h"

static void info_thread(client_t *client)
{
    dprintf(client->fd, _031_, client->thread_ctx->uuid,
        client->thread_ctx->creator->uuid, client->thread_ctx->time,
        client->thread_ctx->title, client->thread_ctx->message);
}

static void info_channel(client_t *client)
{
    dprintf(client->fd, _030_, client->channel_ctx->uuid,
        client->channel_ctx->name, client->channel_ctx->description);
}

static void info_team(client_t *client)
{
    dprintf(client->fd, _029_, client->team_ctx->uuid, client->team_ctx->name,
        client->team_ctx->description);
}

static void info_user(client_t *client)
{
    dprintf(client->fd, _032_, client->user->name, client->user->uuid,
        client->user->loged);
}

void info(server_t *server, client_t *client, char **argv, size_t argc)
{
    (void)server;
    (void)argv;
    if (!client->user || argc != 0) {
        dprintf(client->fd, (!client->user) ? _104_ : _101_);
        return;
    }
    if (client->thread_ctx) {
        info_thread(client);
        return;
    } else if (client->channel_ctx) {
        info_channel(client);
        return;
    }
    if ((client->team_ctx)) {
        info_team(client);
    } else
        info_user(client);
}
