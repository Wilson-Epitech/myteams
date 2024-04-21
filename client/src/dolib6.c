/*
** MYTEAMS PROJECT, 2024
** douser.c
** File description:
** douser.c
*/

#include <stdbool.h>
#include <stdlib.h>

#include "../libs/myteams/logging_client.h"
#include "cmd.h"
#include "libs/mem.h"

void do007(char *buf)
{
    size_t index = 0;
    char *name = NULL;
    char *uuid = NULL;
    char *status = NULL;

    do {
        destroy(name);
        destroy(uuid);
        destroy(status);
        name = get_info(buf, index);
        uuid = get_info(buf, index + 1);
        status = get_info(buf, index + 2);
        if (name && uuid && status) {
            client_print_users(uuid, name, atoi(status));
        }
        index += 3;
    } while (name && uuid && status);
    return;
}

void do105(char *buf)
{
    SMART char *user = get_info(buf, 0);

    client_error_unknown_user(user);
    return;
}

void do107(char *buf)
{
    SMART char *user = get_info(buf, 0);

    client_error_unknown_team(user);
    return;
}

void do108(char *buf)
{
    SMART char *user = get_info(buf, 0);

    client_error_unknown_channel(user);
    return;
}

void do109(char *buf)
{
    SMART char *user = get_info(buf, 0);

    client_error_unknown_thread(user);
    return;
}
