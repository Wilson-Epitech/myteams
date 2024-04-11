/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** run
*/

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#include "cmd.h"
#include "libs/def.h"
#include "server.h"
#include "success.h"

static void reset_socket(server_t *server)
{
    FD_ZERO(&server->read_fd);
    FD_SET(server->fd, &server->read_fd);
    for (size_t i = 0; i < MAX_CLIENT; i++) {
        if (server->clients[i] != NULL && server->clients[i]->fd != 1) {
            FD_SET(server->clients[i]->fd, &server->read_fd);
        }
    }
}

static void handle_server(server_t *server)
{
    int client_fd;
    struct sockaddr_in client_adress = {0};
    socklen_t address_size = sizeof(client_adress);

    if (FD_ISSET(server->fd, &server->read_fd)) {
        client_fd = accept(
            server->fd, (struct sockaddr *)&client_adress, &address_size);
        if (client_fd == -1) {
            PERR_NORET("Accept Failed");
            return;
        }
        if (reply(client_fd, _SUCCESS_000) == FAILURE) {
            PERR_NORET("Write failed");
            close(client_fd);
            return;
        }
        create_client(server, client_fd);
    }
}

static void handle_client(server_t *server)
{
    client_t *client;

    for (size_t i = 0; i < MAX_CLIENT; i++) {
        client = server->clients[i];
        if (client == NULL) {
            continue;
        }
        if (FD_ISSET(client->fd, &server->read_fd)) {
            handle_command(server, client);
        }
    }
}

int run_server(server_t *server)
{
    while (1) {
        reset_socket(server);
        if (select(MAX_CLIENT, &(server->read_fd), NULL, NULL, NULL) == -1) {
            return PERR("Select Failed");
        }
        handle_server(server);
        handle_client(server);
    }
    return SUCCESS;
}
