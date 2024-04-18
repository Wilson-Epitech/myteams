/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** main
*/

#include "server.h"

#include <stdio.h>
#include <string.h>

#include "libs/def.h"
#include "libs/mem.h"

void display_help(void)
{
    puts(
        "\n"
        "USAGE: ./myteams_server port"
        "\n  "
        "\tport is the port number on which the server socket listens."
        "\n");
}

int main(int argc, const char *argv[])
{
    SMART server_t *server = create_server();

    if (argc != 2) {
        return FAILURE;
    }
    if (argc == 2 && strcmp(argv[1], "-help") == 0) {
        display_help();
        return SUCCESS;
    }
    if (init_server(server, argv[1]) == FAILURE) {
        return FAILURE;
    }
    return run_server(server);
}
