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
    SMART char *tmp = NULL;
    size_t size;

    if (file == NULL) {
        return;
    }
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);
    tmp = alloc(size + 1, ptr_free);
    fread(tmp, sizeof(char), size, file);
    tmp[size] = '\0';
    stradd_s(&str, tmp);
    fclose(file);
    dprintf(fd, _006_, str);
}

void help(server_t *server, client_t *client, char **argv, size_t argc)
{
    (void)argv;
    (void)server;
    if (!client->user) {
        dprintf(client->fd, _104_);
        return;
    }
    if (argc != 0) {
        dprintf(client->fd, _101_);
        return;
    }
    display_help(client->fd);
}
