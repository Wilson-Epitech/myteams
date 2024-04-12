/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** server
*/

#pragma once

#include <netinet/in.h>

#include "client.h"

#define MAX_CLIENT 128
#define READ_SIZE 4096

typedef struct server_s {
    char **usernames;
    client_t **clients;
    int port;
    int fd;
    fd_set read_fd;
    struct sockaddr_in address;
} server_t;

// Server Init
int init_server(server_t *server, const char *port);
int run_server(server_t *server);

// Commands
void handle_command(server_t *server, client_t *client);

// Memory Management
server_t *create_server(void);
void server_free(void *ptr);

void create_client(server_t *server, int client_fd);
void client_free(void *ptr);
