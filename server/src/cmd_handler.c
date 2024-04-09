/*
** MYTEAMS PROJECT, 2024
** my-ftp
** File description:
** cmd_handler
*/

#include "reply.h"
#include "server.h"

void handle_command(server_t *server, client_t *client)
{
    (void)server;
    reply(client->fd, "hello\n");
}
