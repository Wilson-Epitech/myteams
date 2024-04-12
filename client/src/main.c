/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>

#include "libs/def.h"
#include "client.h"

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

    if (ac > 1 && is_digit(av[1]))
        port = atoi(av[1]);
    else
        return 84;
    my_client = get_client(port);
    if (my_client == NULL)
        return 84;
    else
        return launch_client(my_client);
}
