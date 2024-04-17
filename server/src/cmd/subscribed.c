/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** subscribed
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "cmd.h"
#include "libs/mem.h"
#include "libs/str.h"
#include "reply.h"
#include "server.h"

static bool is_sub(user_t **subs, char *user_uuid)
{
    for (; *subs; subs++) {
        if (strcmp((*subs)->uuid, user_uuid) == 0) {
            return true;
        }
    }
    return false;
}

static void my_subscribtions(server_t *server, client_t *client)
{
    SMART char *data = strcreate("");

    for (team_t **teams = server->teams; *teams; teams++) {
        if (is_sub((*teams)->subscribers, client->user->uuid)) {
            stradd_c(&data, '[');
            stradd_s(&data, (*teams)->name);
            stradd_s(&data, "] ");
        }
    }
    dprintf(client->fd, _021_, data);
}

static void all_subscribers(
    server_t *server, client_t *client, char *team_uuid)
{
    SMART char *data = strcreate("");
    team_t *team = NULL;

    for (team_t **teams = server->teams; *teams; teams++) {
        if (strcmp((*teams)->uuid, team_uuid) == 0) {
            team = *teams;
        }
    }
    if (!team) {
        dprintf(client->fd, _107_);
        return;
    }
    for (user_t **users = team->subscribers; *users; users++) {
        stradd_c(&data, '[');
        stradd_s(&data, (*users)->name);
        stradd_s(&data, "] ");
    }
    dprintf(client->fd, _022_, team->name, data);
}

void subscribed(server_t *server, client_t *client, char **argv, size_t argc)
{
    if (!client->user) {
        dprintf(client->fd, _104_);
        return;
    }
    if (argc > 1) {
        dprintf(client->fd, _101_);
        return;
    }
    if (argc == 0) {
        my_subscribtions(server, client);
    } else {
        all_subscribers(server, client, *argv);
    }
}
