/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** main
*/

#include <stdio.h>

#include "libs/arr.h"
#include "libs/def.h"
#include "libs/mem.h"
#include "libs/str.h"

void display_help(void)
{
    puts(
        "\n"
        "USAGE: ./myteams_server port"
        "\n  "
        "\tport is the port number on which the server socket listens."
        "\n");
}

int main(UNUSED int argc, UNUSED const char *argv[])
{
    SMART char **arr = split("je suis marius", ' ');

    arrdebug(arr);

    return SUCCESS;
}
