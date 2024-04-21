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

typedef struct dm_s dm_t;
typedef struct reply_s reply_t;
typedef struct thread_s thread_t;
typedef struct channel_s channel_t;
typedef struct team_s team_t;

struct dm_s {
    user_t *sender;
    user_t *receiver;
    time_t time;
    char *message;
};

struct reply_s {
    char *uuid;
    char *body;
    time_t time;
    user_t *creator;
};

struct thread_s {
    char *uuid;
    time_t time;
    char *title;
    char *message;
    user_t *creator;
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
    user_t **users;
    client_t **clients;
    team_t **teams;
    dm_t **dms;
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

team_t *create_team(
    server_t *, user_t *creator, char *name, char *description);
void team_free(void *ptr);

channel_t *create_channel(char *name, char *description, team_t *parent);
void channel_free(void *ptr);

thread_t *create_thread(
    char *title, char *message, channel_t *parent, user_t *creator);
void thread_free(void *ptr);

reply_t *create_reply(char *body, user_t *creator);
void reply_free(void *ptr);

dm_t *create_dm(
    server_t *server, user_t *sender, user_t *receiver, char *message);
void dm_free(void *ptr);

// Utils
user_t *find_user(server_t *server, char *username);
user_t *find_user_by_uuid(user_t **users, char *uuid);
team_t *find_team_by_name(team_t **teams, char *name);
team_t *find_team(team_t **teams, char *team_uuid);
channel_t *find_channel(channel_t **channels, char *channel_uuid);
thread_t *find_thread(thread_t **threads, char *thread_uuid);
dm_t **find_dms(dm_t **dms, user_t *sender, user_t *receiver);
client_t *find_client(client_t **clients, user_t *user);
channel_t *find_channel_by_name(channel_t **channels, char *name);
thread_t *find_thread_by_name(thread_t **threads, char *name);

void remove_quote(char **arr);
char *generate_uuid(void);
