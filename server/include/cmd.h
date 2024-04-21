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
    void (*function)(server_t *, client_t *, char **, size_t);
} cmd_t;

#define DECLARE(name) void name(server_t *, client_t *, char **, size_t)
#define BRACKET_LEFT {
#define BRACKET_RIGHT }
#define ARGUMENTS(name, argc) BRACKET_LEFT "/" #name, argc, name BRACKET_RIGHT

DECLARE(login);
DECLARE(logout);
DECLARE(help);
DECLARE(users);
DECLARE(user);
DECLARE(create);
DECLARE(use);
DECLARE(subscribed);
DECLARE(subscribe);
DECLARE(unsubscribe);
DECLARE(list);
DECLARE(info);
DECLARE(send_cmd);
DECLARE(messages);

static const cmd_t COMMANDS[] = {
    ARGUMENTS(login, 1),
    ARGUMENTS(logout, 0),
    ARGUMENTS(help, 0),
    ARGUMENTS(users, 0),
    ARGUMENTS(user, 1),
    ARGUMENTS(create, 1),
    ARGUMENTS(use, 0),
    ARGUMENTS(subscribed, 0),
    ARGUMENTS(subscribe, 1),
    ARGUMENTS(unsubscribe, 1),
    ARGUMENTS(list, 0),
    ARGUMENTS(info, 0),
    ARGUMENTS(send_cmd, 2),
    ARGUMENTS(messages, 1),
};

static const size_t NB_COMMANDS = sizeof(COMMANDS) / sizeof(cmd_t);
