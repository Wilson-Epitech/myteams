/*
** MYTEAMS PROJECT, 2024
** cmd.h
** File description:
** cmd.h
*/

#pragma once

#include <stddef.h>

char *search_at_info(char *buf, int in);

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
DECLARE(do007);
DECLARE(do104);
DECLARE(do105);
DECLARE(do107);
DECLARE(do108);
DECLARE(do109);

static const cmd_t COMMANDS[] = {
    ARGUMENTS(do003),
    ARGUMENTS(do004),
    ARGUMENTS(do007),
    ARGUMENTS(do104),
    ARGUMENTS(do105),
    ARGUMENTS(do107),
    ARGUMENTS(do108),
    ARGUMENTS(do109),

};

static const size_t NB_COMMANDS = sizeof(COMMANDS) / sizeof(cmd_t);
