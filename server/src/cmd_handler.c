/*
** MYTEAMS PROJECT, 2024
** my-ftp
** File description:
** cmd_handler
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "cmd.h"
#include "libs/arr.h"
#include "libs/def.h"
#include "libs/mem.h"
#include "libs/str.h"
#include "reply.h"
#include "server.h"

// the clients become zombies when disconnected without quitting
// the check "end == NULL" prevents the server from crashing
// because when the client disconnect in a wrong way,
// the server thinks there's something to read so he tries to.
// but he finds nothing and later, the command parsing fails.
static char **get_input(int fd)
{
    char buff[READ_SIZE + 1] = {0};
    char *end;

    if (read(fd, buff, READ_SIZE) == -1) {
        return NULL;
    }
    end = strstr(buff, "\n");
    if (end == NULL) {
        return NULL;
    }
    *end = '\0';
    return split_keep_quote(buff, ' ');
}

// doesnt accept empty args like ""
static bool is_quoted(char *str)
{
    size_t len = strlen(str);

    if (len <= 2 || str[0] != '"' || str[len - 1] != '"') {
        return false;
    }
    return true;
}

static int valid_argv(char **argv)
{
    while (*argv) {
        if (!is_quoted(*argv)) {
            return FAILURE;
        }
        argv++;
    }
    return SUCCESS;
}

// todo: should an empty command be responded with an error or ignored ?
void handle_command(server_t *server, client_t *client)
{
    SMART char **argv = get_input(client->fd);
    size_t argc;

    if (argv == NULL || *argv == NULL)
        return;
    if (valid_argv(argv + 1) == FAILURE) {
        dprintf(client->fd, _102_);
        return;
    }
    argc = arrlen(argv + 1);
    for (size_t i = 0; i < NB_COMMANDS; i++) {
        if (strcmp(COMMANDS[i].name, *argv) != 0)
            continue;
        if (COMMANDS[i].argc > argc) {
            dprintf(client->fd, _101_);
        } else
            COMMANDS[i].function(server, client, argv + 1, argc);
        return;
    }
    dprintf(client->fd, _100_);
}
