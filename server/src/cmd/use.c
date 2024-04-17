/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** use
*/

#include <stdio.h>
#include <string.h>

#include "libs/arr.h"
#include "reply.h"
#include "server.h"

static void set_team_context(server_t *server, client_t *client, char **argv)
{
    team_t *team = find_team(server->teams, *argv);

    if (team) {
        client->team_ctx = team;
        client->channel_ctx = NULL;
        client->thread_ctx = NULL;
        dprintf(client->fd, _018_, team->name);
    } else {
        dprintf(client->fd, _107_);
    }
}

static void set_channel_context(
    server_t *server, client_t *client, char **argv)
{
    team_t *team = find_team(server->teams, *argv);
    channel_t *channel =
        (team) ? find_channel(team->channels, *(argv + 1)) : NULL;

    if (team && channel) {
        client->team_ctx = team;
        client->channel_ctx = channel;
        client->thread_ctx = NULL;
        dprintf(client->fd, _019_, client->team_ctx->name,
            client->channel_ctx->name);
    } else {
        dprintf(client->fd, _108_);
    }
}

static void set_thread_context(server_t *server, client_t *client, char **argv)
{
    team_t *team = find_team(server->teams, *argv);
    channel_t *channel =
        (team) ? find_channel(team->channels, *(argv + 1)) : NULL;
    thread_t *thread =
        (channel) ? find_thread(channel->threads, *(argv + 2)) : NULL;

    if (team && channel && thread) {
        client->team_ctx = team;
        client->channel_ctx = channel;
        client->thread_ctx = thread;
        dprintf(client->fd, _020_, team->name, channel->name, thread->title);
    } else {
        dprintf(client->fd, _109_);
    }
}

static void set_root_context(client_t *client)
{
    client->team_ctx = NULL;
    client->channel_ctx = NULL;
    client->thread_ctx = NULL;
    dprintf(client->fd, _017_);
}

static int if_subbed(
    server_t *server, client_t *client, char **argv, size_t argc)
{
    team_t *team = find_team(server->teams, *argv);

    if (!team) {
        return dprintf(client->fd, _107_);
    }
    if (!arr_has(team->subscribers, client->user)) {
        return dprintf(client->fd, _104_);
    }
    if (argc == 0) {
        set_root_context(client);
    }
    if (argc == 1) {
        set_team_context(server, client, argv);
    }
    if (argc == 2) {
        set_channel_context(server, client, argv);
    } else if (argc == 3) {
        set_thread_context(server, client, argv);
    }
    return 0;
}

void use(server_t *server, client_t *client, char **argv, size_t argc)
{
    if (!client->user || argc > 3) {
        dprintf(client->fd, (!client->user) ? _104_ : _101_);
        return;
    }
    if_subbed(server, client, argv, argc);
}
