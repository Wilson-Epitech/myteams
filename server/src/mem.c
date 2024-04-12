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

#include "libs/arr.h"
#include "libs/def.h"
#include "server.h"

void server_free(void *ptr)
{
    server_t *server = ptr;

    if (server == NULL) {
        return;
    }
    if (server->fd != -1) {
        close(server->fd);
    }
    destroy(server->usernames);
    destroy(server->clients);
    ptr_free(server);
}

// should load the db
server_t *create_server(void)
{
    server_t *server = alloc(sizeof(server_t), server_free);

    if (server == NULL) {
        return NULL;
    }
    server->usernames = arr_alloc(sizeof(char *), 1);
    server->clients = arr_alloc(sizeof(client_t *), 1);
    server->port = 0;
    server->fd = -1;
    FD_ZERO(&(server->read_fd));
    memset(&(server->address), 0, sizeof(server->address));
    return server;
}

void client_free(void *ptr)
{
    client_t *client = ptr;

    if (client == NULL) {
        return;
    }
    if (client->fd != -1) {
        close(client->fd);
    }
    destroy(client->username);
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
    client_t *client = alloc(sizeof(client_t), client_free);

    if (client == NULL) {
        PERR_NORET("Couldn't Alloc Client");
        close(client_fd);
        return;
    }
    client->fd = client_fd;
    client->username = NULL;
    client->context = ROOT;
    arr_pushback(&(server->clients), client);
}
