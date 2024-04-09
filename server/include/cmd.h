/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** cmd
*/

#pragma once

#include "server.h"

#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512

typedef struct cmd_s {
    const char *name;
    void (*function)(server_t *, char **);
} cmd_t;
