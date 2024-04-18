/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>

#include "client.h"
#include "libs/def.h"

int is_digit(const char *str)
{
    for (int i = 0; str[i] == '\0'; i += 1) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}

int main(int ac, const char *av[])
{
    int port = 0;
    client_t *my_client;

    if (ac > 2 && is_digit(av[2]))
        port = atoi(av[2]);
    else {
        PERR_NORET("Invalid Port");
        return 84;
    }
    my_client = get_client(port, av[1]);
    if (my_client == NULL) {
        PERR_NORET("Client Alloc failed");
        return 84;
    }
    launch_client(my_client);
    free(my_client);
    return 0;
}
