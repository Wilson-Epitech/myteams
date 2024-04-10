/*
** MYTEAMS PROJECT, 2024
** my-ftp
** File description:
** cmd_handler
*/

#include <string.h>
#include <unistd.h>

#include "libs/mem.h"
#include "libs/str.h"
#include "reply.h"
#include "server.h"

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
    return split(buff, ' ');
}

void handle_command(server_t *server, client_t *client)
{
    SMART char **tokens = get_input(client->fd);

    if (tokens == NULL) {
        return;
    }

    (void)server;
    reply(client->fd, "input received\n");
}
