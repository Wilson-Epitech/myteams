/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** create
*/

#include <stdio.h>
#include <string.h>

#include "../libs/myteams/logging_server.h"
#include "cmd.h"
#include "libs/arr.h"
#include "reply.h"
#include "server.h"

static void cr_team(
    server_t *server, client_t *client, char **argv, size_t argc)
{
    team_t *team;

    if (argc == 2) {
        team = create_team(server, client->user, *argv, *(argv + 1));
        if (team) {
            arr_pushback(&(server->teams), team);
            dprintf(
                client->fd, _009_, team->uuid, team->name, team->description);
            server_event_team_created(
                team->uuid, team->name, team->creator->uuid);
        } else {
            dprintf(client->fd, _106_);
        }
    } else {
        dprintf(client->fd, _101_);
    }
}

static void cr_channel(
    server_t *server, client_t *client, char **argv, size_t argc)
{
    channel_t *channel;

    if (argc == 2) {
        channel = create_channel(server, *argv, *(argv + 1), client->team_ctx);
        if (channel) {
            arr_pushback(&(client->team_ctx->channels), channel);
            dprintf(client->fd, _010_, channel->uuid, channel->name,
                channel->description);
            server_event_channel_created(
                client->user->uuid, channel->uuid, channel->name);
        } else {
            dprintf(client->fd, _106_);
        }
    } else {
        dprintf(client->fd, _101_);
    }
}

static void cr_thread(
    server_t *server, client_t *client, char **argv, size_t argc)
{
    thread_t *thread;

    if (argc == 2) {
        thread =
            create_thread(server, *argv, *(argv + 1), client->channel_ctx);
        if (thread) {
            arr_pushback(&(client->channel_ctx->threads), thread);
            dprintf(client->fd, _011_, thread->uuid, client->user->uuid,
                thread->time, thread->title, thread->message);
            server_event_thread_created(client->channel_ctx->uuid,
                thread->uuid, client->user->uuid, thread->title,
                thread->message);
        } else {
            dprintf(client->fd, _106_);
        }
    } else {
        dprintf(client->fd, _101_);
    }
}

static void cr_reply(
    server_t *server, client_t *client, char **argv, size_t argc)
{
    reply_t *reply;

    if (argc == 1) {
        reply = create_reply(server, *argv);
        if (reply) {
            arr_pushback(&(client->thread_ctx->replies), reply);
            dprintf(client->fd, _012_, client->thread_ctx->uuid,
                client->user->uuid, reply->time, reply->body);
            server_event_reply_created(
                client->thread_ctx->uuid, client->user->uuid, reply->body);
        } else {
            dprintf(client->fd, _106_);
        }
    } else {
        dprintf(client->fd, _101_);
    }
}

void create(server_t *server, client_t *client, char **argv, size_t argc)
{
    if (!client->user) {
        dprintf(client->fd, _104_);
        return;
    }
    if (client->team_ctx == NULL) {
        cr_team(server, client, argv, argc);
        return;
    }
    if (client->channel_ctx == NULL) {
        cr_channel(server, client, argv, argc);
        return;
    }
    if (client->thread_ctx == NULL) {
        cr_thread(server, client, argv, argc);
        return;
    }
    cr_reply(server, client, argv, argc);
}
