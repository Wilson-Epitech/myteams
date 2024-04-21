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

void do029(char *buf)
{
    SMART char *uuid = get_info(buf, 0);
    SMART char *name = get_info(buf, 1);
    SMART char *description = get_info(buf, 2);

    client_print_team(uuid, name, description);
}

void do030(char *buf)
{
    SMART char *uuid = get_info(buf, 0);
    SMART char *name = get_info(buf, 1);
    SMART char *description = get_info(buf, 2);

    client_print_channel(uuid, name, description);
}

void do031(char *buf)
{
    SMART char *uuid = get_info(buf, 0);
    SMART char *user_uuid = get_info(buf, 1);
    SMART char *time = get_info(buf, 2);
    SMART char *title = get_info(buf, 3);
    SMART char *body = get_info(buf, 4);

    client_print_thread(uuid, user_uuid, atol(time), title, body);
}

void do032(char *buf)
{
    SMART char *uuid = get_info(buf, 0);
    SMART char *name = get_info(buf, 1);
    SMART char *status = get_info(buf, 2);

    client_print_user(uuid, name, atol(status));
}

void do143(char *buf)
{
    (void)buf;
    client_error_already_exist();
}
