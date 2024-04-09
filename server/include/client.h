/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** client
*/

#pragma once

enum context {
    NONE = 1,
    TEAM = 2,
    CHANNEL = 4,
    THREAD = 8,
};

typedef struct client_s {
    int context;
} client_t;
