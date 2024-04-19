/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>

#include "../libs/myteams/logging_client.h"
#include "client.h"
#include "libs/def.h"
#include "libs/mem.h"

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
    client_t *client;

    if (ac > 2 && is_digit(av[2]))
        port = atoi(av[2]);
    else {
        PERR_NORET("Invalid Port");
        return 84;
    }
    client = get_client(port, av[1]);
    if (client == NULL) {
        PERR_NORET("Client Alloc failed");
        return 84;
    }
    if (launch_client(client) == 0 && client->uuid != NULL)
        client_event_logged_out(client->uuid, client->name);
    try_free(client->name);
    try_free(client->uuid);
    free(client);
    return 0;
}
