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
    char *uuid;
    char *name;
    bool loged;
} user_t;

typedef struct reply_s reply_t;
typedef struct thread_s thread_t;
typedef struct channel_s channel_t;
typedef struct team_s team_t;

struct reply_s {
    char *uuid;
    char *body;
    time_t time;
};

struct thread_s {
    char *uuid;
    time_t time;
    char *title;
    char *message;
    reply_t **replies;
};

struct channel_s {
    char *uuid;
    char *name;
    char *description;
    thread_t **threads;
};

struct team_s {
    char *uuid;
    char *name;
    char *description;
    user_t *creator;
    user_t **subscribers;
    channel_t **channels;
};

typedef struct client_s {
    int fd;
    user_t *user;
    team_t *team_ctx;
    channel_t *channel_ctx;
    thread_t *thread_ctx;
} client_t;

// missing teams, channels, thread, reply, dms
typedef struct server_s {
    size_t uuid;
    user_t **users;
    client_t **clients;
    team_t **teams;
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

void create_user(server_t *server, char *name);
void user_free(void *ptr);

team_t *create_team(
    server_t *, user_t *creator, char *name, char *description);
void team_free(void *ptr);

channel_t *create_channel(
    server_t *server, char *name, char *description, team_t *parent);
void channel_free(void *ptr);

thread_t *create_thread(
    server_t *server, char *title, char *message, channel_t *parent);
void thread_free(void *ptr);

reply_t *create_reply(server_t *server, char *body);
void reply_free(void *ptr);

// Utils
user_t *find_user(server_t *server, char *username);

// Save
// void save_user(server_t *server, char *username);
// todo: all save

// Temporary (will be replaced with the real generation)
char *generate_uuid(server_t *server);
void remove_quote(char **arr);
