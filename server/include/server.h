/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** server
*/

#pragma once

#include <netinet/in.h>

#define MAX_CLIENT 128
#define READ_SIZE 4096

#include <stdbool.h>

typedef struct user_s {
    char *name;
    char *uuid;
    bool loged;
} user_t;

enum context {
    ROOT = 1,
    TEAM = 2,
    CHANNEL = 4,
    THREAD = 8,
};

typedef struct client_s {
    int fd;
    user_t *user;
    enum context context;
} client_t;

typedef struct thread_s {
} thread_t;

typedef struct channel_s {
} channel_t;

typedef struct team_s {
} team_t;

// missing teams, channels, thread, reply, dms
typedef struct server_s {
    user_t **users;
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

user_t *create_user(server_t *server, char *name);
void user_free(void *ptr);

// Utils
user_t *find_user(server_t *server, char *username);
user_t *save_user(server_t *server, char *username);
