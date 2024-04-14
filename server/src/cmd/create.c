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
#include "reply.h"
#include "server.h"

static void cr_team(
    server_t *server, client_t *client, char **argv, size_t argc)
{
    team_t *team;

    if (argc == 2) {
        team = create_team(server, client->user, *argv, *(argv + 1));
        if (team) {
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
    if (argc == 2) {
        create_channel(server, *argv, *(argv + 1));
    } else {
        dprintf(client->fd, _101_);
    }
}

static void cr_thread(
    server_t *server, client_t *client, char **argv, size_t argc)
{
    if (argc == 2) {
        create_thread(server, *argv, *(argv + 1));
    } else {
        dprintf(client->fd, _101_);
    }
}

static void cr_reply(
    server_t *server, client_t *client, char **argv, size_t argc)
{
    if (argc == 1) {
        create_reply(server, *argv);
    } else {
        dprintf(client->fd, _101_);
    }
}

void create(server_t *server, client_t *client, char **argv, size_t argc)
{
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
