/*
** MYTEAMS PROJECT, 2024
** cmd.h
** File description:
** cmd.h
*/

#pragma once

#include <stddef.h>

typedef struct cmd_s {
    const char *name;
    void (*function)(char *);
} cmd_t;

#define DECLARE(name) void name(char *)
#define BRACKET_LEFT {
#define BRACKET_RIGHT }
#define ARGUMENTS(name) BRACKET_LEFT #name, name BRACKET_RIGHT

DECLARE(do001);
// DECLARE(logout);
// DECLARE(help);

static const cmd_t COMMANDS[] = {
    ARGUMENTS(do001),
    //    ARGUMENTS(logout, 0),
    //    ARGUMENTS(help, 0),
    //    ARGUMENTS(users, 0),
    //    ARGUMENTS(user, 1),
    //    ARGUMENTS(create, 1),
    //    ARGUMENTS(use, 0),
    //    ARGUMENTS(subscribed, 0),
    //    ARGUMENTS(subscribe, 1),
    //    ARGUMENTS(unsubscribe, 1),
    //    ARGUMENTS(list, 0),
    //    ARGUMENTS(info, 0),
    //    ARGUMENTS(send_cmd, 2),
    //    ARGUMENTS(messages, 1),
};

static const size_t NB_COMMANDS = sizeof(COMMANDS) / sizeof(cmd_t);
