/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** client
*/

#pragma once

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

typedef struct client_s {
    int fd;
    int status;
} client_t;

client_t *get_client(int);
int launch_client(client_t *client);
