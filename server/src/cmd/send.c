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

void send_cmd(server_t *server, client_t *client, char **argv, size_t argc)
{
    user_t *receiver = NULL;

    if (!client->user) {
        dprintf(client->fd, _104_);
        return;
    }
    if (argc != 2) {
        dprintf(client->fd, _101_);
        return;
    }
    receiver = find_user_by_uuid(server, *argv);
    if (!receiver) {
        dprintf(client->fd, _105_);
        return;
    }
    create_dm(server, client->user, receiver, *(argv + 1));
    dprintf(client->fd, _033_, receiver->name, *(argv + 1));
}
