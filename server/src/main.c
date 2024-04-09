/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** main
*/

#include <stdio.h>

#include "libs/def.h"

void display_help(void)
{
    puts(
        "\n"
        "USAGE: ./myteams_server port"
        "\n  "
        "port is the port number on which the server socket listens."
        "\n");
}

int main(int argc, const char *argv[])
{
    printf("server\n");
    printf("argc=[%d]\n", argc);
    while (*argv) {
        printf("%s\n", *argv);
        argv++;
    }
    return SUCCESS;
}
