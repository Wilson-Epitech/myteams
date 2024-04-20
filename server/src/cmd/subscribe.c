/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** subscribed
*/

#include <stdbool.h>
#include <stdio.h>

#include "../libs/myteams/logging_server.h"
#include "cmd.h"
#include "libs/arr.h"
#include "reply.h"
#include "server.h"

void subscribe(server_t *server, client_t *client, char **argv, size_t argc)
{
    team_t *team;

    if (!client->user) {
        dprintf(client->fd, _104_);
        return;
    }
    if (argc != 1) {
        dprintf(client->fd, _101_);
        return;
    }
    team = find_team(server->teams, *argv);
    if (!team) {
        dprintf(client->fd, _107_, *argv);
        return;
    }
    if (!arr_has(team->subscribers, client->user)) {
        arr_pushback(&(team->subscribers), client->user);
        server_event_user_subscribed(team->uuid, client->user->uuid);
        dprintf(client->fd, _023_, client->user->uuid, team->uuid);
    }
}
