/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** logout
*/

#include <stdbool.h>
#include <stdio.h>

#include "../libs/myteams/logging_server.h"
#include "cmd.h"
#include "reply.h"
#include "server.h"

static void send_notif(server_t *server, client_t *client, dm_t *dm)
{
    if (dm->receiver->loged) {
        dprintf(find_client(server->clients, dm->receiver)->fd, _035_,
            dm->sender->uuid, dm->message);
    }
    dprintf(client->fd, _033_, dm->receiver->name, dm->message);
    server_event_private_message_sended(
        dm->sender->uuid, dm->receiver->uuid, dm->message);
}

void send_cmd(server_t *server, client_t *client, char **argv, size_t argc)
{
    user_t *receiver = NULL;
    dm_t *dm = NULL;

    if (!client->user || argc != 2) {
        dprintf(client->fd, (!client->user) ? _104_ : _101_);
        return;
    }
    receiver = find_user_by_uuid(server->users, *argv);
    if (!receiver) {
        dprintf(client->fd, _105_, *argv);
        return;
    }
    if (receiver == client->user) {
        dprintf(client->fd, _104_);
        return;
    }
    dm = create_dm(server, client->user, receiver, *(argv + 1));
    send_notif(server, client, dm);
}
