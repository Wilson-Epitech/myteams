/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** mem
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "cmd.h"
#include "database.h"
#include "libs/arr.h"
#include "libs/def.h"
#include "libs/mem.h"
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
    save_database(server);
    while (*(server->clients)) {
        logout(server, *(server->clients), NULL, 0);
    }
    destroy(server->teams);
    destroy(server->dms);
    destroy(server->users);
    destroy(server->clients);
    ptr_free(ptr);
}

// static int find_highest_uuid(server_t*server)
// {
//     int high = 0;

//     // for (user_t **user)
// }

// load users
// load dms
// load teams
server_t *create_server(void)
{
    server_t *server = alloc(sizeof(server_t), server_free);

    if (server == NULL) {
        return NULL;
    }
    server->users = load_users();
    server->clients = arr_alloc(1);
    server->teams = load_teams(server->users);
    server->dms = load_dms(server->users);
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
    client->user = NULL;
    client->team_ctx = NULL;
    client->channel_ctx = NULL;
    client->thread_ctx = NULL;
    arr_pushback(&(server->clients), client);
}
