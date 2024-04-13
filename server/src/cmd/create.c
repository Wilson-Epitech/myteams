/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** create
*/

#include <stdio.h>
#include <string.h>

#include "cmd.h"
#include "libs/mem.h"
#include "libs/str.h"
#include "reply.h"
#include "server.h"

static void create_team(
    server_t *server, client_t *client, char **argv, size_t argc)
{
}

static void create_channel(
    server_t *server, client_t *client, char **argv, size_t argc)
{
}

static void create_thread(
    server_t *server, client_t *client, char **argv, size_t argc)
{
}

static void create_reply(
    server_t *server, client_t *client, char **argv, size_t argc)
{
}

void create(server_t *server, client_t *client, char **argv, size_t argc)
{
    if (client->context == NONE) {
        create_team(server, client, argv, argc);
        return;
    }
    if (client->context == TEAM) {
        create_channel(server, client, argv, argc);
        return;
    }
    if (client->context == CHANNEL) {
        create_thread(server, client, argv, argc);
        return;
    }
    if (client->context == THREAD) {
        create_reply(server, client, argv, argc);
        return;
    }
}
