/*
** MYTEAMS PROJECT, 2024
** my-ftp
** File description:
** cmd_handler
*/

#include <string.h>
#include <unistd.h>

#include "cmd.h"
#include "error.h"
#include "libs/arr.h"
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
    return split_teams(buff, ' ');
}

void handle_command(server_t *server, client_t *client)
{
    SMART char **argv = get_input(client->fd);
    size_t argc;

    if (argv == NULL || *argv == NULL) {
        return;
    }
    argc = arrlen(*argv + 1);
    for (size_t i = 0; i < NB_COMMANDS; i++) {
        if (strcmp(COMMANDS[i].name, *argv) == 0 && COMMANDS[i].argc <= argc) {
            COMMANDS[i].function(server, client, argv + 1);
            return;
        }
    }
    reply(client->fd, _ERROR_100);
}
