/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** mem
*/

#include "libs/mem.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "libs/def.h"
#include "server.h"

void server_free(void *ptr)
{
    server_t *server = ptr;

    if (server != NULL && server->fd != -1) {
        close(server->fd);
    }
    destroy(server->clients);
    ptr_free(server);
}

server_t *create_server(void)
{
    server_t *server = alloc(sizeof(server_t), server_free);

    if (server == NULL) {
        return NULL;
    }
    server->fd = -1;
    server->nb_client = 0;
    server->clients = arr_alloc(sizeof(client_t *), MAX_CLIENT);
    memset(server->clients, 0, sizeof(client_t *) * MAX_CLIENT);
    return server;
}

void client_free(void *ptr)
{
    client_t *client = ptr;

    if (client != NULL && client->fd != -1) {
        close(client->fd);
    }
    try_free(client->username);
    ptr_free(ptr);
}

// should not be needed
// if (server->cc == MAX_CLIENT - 1) {
//     PERR_NORET("Too many clients, can't handle more");
//     close(client_fd);
//     return;
// }
void create_client(server_t *server, int client_fd)
{
    client_t *new = alloc(sizeof(client_t), client_free);

    if (new == NULL) {
        PERR_NORET("Couldn't Alloc Client");
        close(client_fd);
        return;
    }
    new->fd = client_fd;
    new->username = NULL;
    server->clients[server->nb_client] = new;
    server->nb_client += 1;
}
