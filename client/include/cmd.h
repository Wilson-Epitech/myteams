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

DECLARE(do003);
DECLARE(do004);
DECLARE(do104);

static const cmd_t COMMANDS[] = {
    ARGUMENTS(do003),
    ARGUMENTS(do004),
    ARGUMENTS(do104),

};

static const size_t NB_COMMANDS = sizeof(COMMANDS) / sizeof(cmd_t);
