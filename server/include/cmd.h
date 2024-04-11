/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** cmd
*/

#pragma once

#include <stdlib.h>

#include "server.h"

#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512

typedef struct cmd_s {
    const char *name;
    size_t argc;
    void (*function)(server_t *, client_t *, char **);
} cmd_t;

void login(server_t *server, client_t *client, char **args);
void logout(server_t *server, client_t *client, char **args);

static const cmd_t COMMANDS[] = {
    // {"/login", 1, login},
};

static const size_t NB_COMMANDS = sizeof(COMMANDS) / sizeof(cmd_t);
