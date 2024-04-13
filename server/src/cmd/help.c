/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** help
*/

#include <stdio.h>

#include "cmd.h"
#include "libs/mem.h"
#include "libs/str.h"
#include "reply.h"
#include "server.h"

static void display_help(int fd)
{
    FILE *file = fopen("protocol.yaml", "r");
    SMART char *str = strcreate("");
    char c;

    if (file == NULL) {
        return;
    }
    for (c = fgetc(file); c != EOF; c = fgetc(file)) {
        stradd_c(&str, c);
    }
    fclose(file);
    dprintf(fd, _006_, str);
}

void help(server_t *server, client_t *client, char **argv, size_t argc)
{
    (void)argv;
    (void)server;
    if (argc != 0) {
        dprintf(client->fd, _101_);
        return;
    }
    if (client->user && client->user->loged) {
        display_help(client->fd);
    } else {
        dprintf(client->fd, _104_);
    }
}
