/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** init
*/

#include <ctype.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "libs/def.h"
#include "server.h"

static int bind_server_socket(server_t *server)
{
    server->adress.sin_family = AF_INET;
    server->adress.sin_addr.s_addr = INADDR_ANY;
    server->adress.sin_port = htons(server->port);
    if (bind(server->fd, (struct sockaddr *)(&(server->adress)),
            sizeof(struct sockaddr_in)) == -1) {
        return PERR("Binding Failed");
    }
    return SUCCESS;
}

static int set_server_port(server_t *server, const char *port)
{
    for (size_t i = 0; port[i]; i++) {
        if (!isdigit(port[i])) {
            return PERR("Invalid Port");
        }
    }
    server->port = atoi(port);
    if (server->port <= 0 || server->port >= 65535) {
        return PERR("Invalid Port");
    }
    return SUCCESS;
}

static int init_server_socket(server_t *server)
{
    int optval = 1;

    server->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->fd == -1) {
        return PERR("Server Opening Failed");
    }
    if (setsockopt(server->fd, SOL_SOCKET, SO_REUSEADDR, &optval,
            sizeof(optval)) == -1) {
        return PERR("Set Socket Option failed");
    }
    return SUCCESS;
}

static int start_server_listening(server_t *server)
{
    if (listen(server->fd, SOMAXCONN) == -1) {
        return PERR("Listen Failed");
    }
    return SUCCESS;
}

int init_server(server_t *server, const char *port)
{
    if (server == NULL) {
        return PERR("Malloc Failed");
    }
    if (set_server_port(server, port) == FAILURE ||
        init_server_socket(server) == FAILURE ||
        bind_server_socket(server) == FAILURE ||
        start_server_listening(server) == FAILURE) {
        return FAILURE;
    }
    return SUCCESS;
}
