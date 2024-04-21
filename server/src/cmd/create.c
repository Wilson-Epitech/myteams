/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** create
*/

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "../libs/myteams/logging_server.h"
#include "cmd.h"
#include "libs/arr.h"
#include "reply.h"
#include "server.h"

static void event_team_created(void *_client, va_list ap)
{
    client_t *client = _client;
    team_t *team = va_arg(ap, team_t *);

    if (client->user) {
        dprintf(client->fd, _009_, team->uuid, team->name, team->description);
    }
}

static void cr_team(
    server_t *server, client_t *client, char **argv, size_t argc)
{
    team_t *team;

    if (argc == 2) {
        team = create_team(server, client->user, *argv, *(argv + 1));
        if (team) {
            arr_foreach_arg(server->clients, event_team_created, team);
            arr_pushback(&(server->teams), team);
            server_event_team_created(
                team->uuid, team->name, team->creator->uuid);
            dprintf(
                client->fd, _039_, team->uuid, team->name, team->description);
        } else {
            dprintf(client->fd, _106_);
        }
    } else {
        dprintf(client->fd, _101_);
    }
}

static void event_channel_created(void *_user, va_list ap)
{
    user_t *user = _user;
    server_t *server = va_arg(ap, server_t *);
    channel_t *channel = va_arg(ap, channel_t *);
    client_t *except = va_arg(ap, client_t *);
    client_t *client = find_client(server->clients, user);

    if (client != except && client->user) {
        dprintf(client->fd, _010_, channel->uuid, channel->name,
            channel->description);
    }
}

static void cr_channel(
    server_t *server, client_t *client, char **argv, size_t argc)
{
    channel_t *channel;

    if (argc == 2) {
        channel = create_channel(*argv, *(argv + 1), client->team_ctx);
        if (channel) {
            arr_pushback(&(client->team_ctx->channels), channel);
            arr_foreach_arg(client->team_ctx->subscribers,
                event_channel_created, server, channel, client);
            server_event_channel_created(
                client->user->uuid, channel->uuid, channel->name);
            dprintf(client->fd, _040_, channel->uuid, channel->name,
                channel->description);
        } else {
            dprintf(client->fd, _106_);
        }
    } else {
        dprintf(client->fd, _101_);
    }
}

static void event_thread_created(void *_user, va_list ap)
{
    user_t *user = _user;
    server_t *server = va_arg(ap, server_t *);
    thread_t *thread = va_arg(ap, thread_t *);
    client_t *except = va_arg(ap, client_t *);
    client_t *client = find_client(server->clients, user);

    if (client != except && client->user) {
        dprintf(client->fd, _011_, thread->uuid, thread->creator->uuid,
            thread->time, thread->title, thread->message);
    }
}

static void cr_thread(
    server_t *server, client_t *client, char **argv, size_t argc)
{
    thread_t *thread;

    if (argc == 2) {
        thread = create_thread(
            *argv, *(argv + 1), client->channel_ctx, client->user);
        if (thread) {
            arr_pushback(&(client->channel_ctx->threads), thread);
            arr_foreach_arg(client->team_ctx->subscribers,
                event_thread_created, server, thread, client);
            server_event_thread_created(client->channel_ctx->uuid,
                thread->uuid, client->user->uuid, thread->title,
                thread->message);
            dprintf(client->fd, _041_, thread->uuid, thread->creator->uuid,
                thread->time, thread->title, thread->message);
        } else {
            dprintf(client->fd, _106_);
        }
    } else {
        dprintf(client->fd, _101_);
    }
}

static void event_reply_created(void *_user, va_list ap)
{
    user_t *user = _user;
    server_t *server = va_arg(ap, server_t *);
    team_t *team = va_arg(ap, team_t *);
    thread_t *thread = va_arg(ap, thread_t *);
    reply_t *reply = va_arg(ap, reply_t *);
    client_t *except = va_arg(ap, client_t *);
    client_t *client = find_client(server->clients, user);

    if (client != except && client->user) {
        dprintf(client->fd, _012_, team->uuid, thread->uuid,
            reply->creator->uuid, reply->body);
    }
}

static void cr_reply(
    server_t *server, client_t *client, char **argv, size_t argc)
{
    reply_t *reply;

    if (argc == 1) {
        reply = create_reply(*argv, client->user);
        if (reply) {
            arr_pushback(&(client->thread_ctx->replies), reply);
            arr_foreach_arg(client->team_ctx->subscribers, event_reply_created,
                server, client->team_ctx, client->thread_ctx, reply, client);
            server_event_reply_created(
                client->thread_ctx->uuid, client->user->uuid, reply->body);
            dprintf(client->fd, _042_, client->thread_ctx->uuid,
                client->user->uuid, reply->time, reply->body);
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
