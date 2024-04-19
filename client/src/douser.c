/*
** MYTEAMS PROJECT, 2024
** douser.c
** File description:
** douser.c
*/

#include <stdlib.h>

#include "../libs/myteams/logging_client.h"
#include "cmd.h"

void do007(char *buf)
{
    char *user = search_at_info(buf, 0);
    char *uuid = search_at_info(buf, 1);

    client_event_logged_out(uuid, user);
    free(user);
    free(uuid);
    return;
}

void do105(char *buf)
{
    char *user = search_at_info(buf, 0);

    client_error_unknown_user(user);
    free(user);
    return;
}

void do107(char *buf)
{
    char *user = search_at_info(buf, 0);

    client_error_unknown_team(user);
    free(user);
    return;
}

void do108(char *buf)
{
    char *user = search_at_info(buf, 0);

    client_error_unknown_channel(user);
    free(user);
    return;
}

void do109(char *buf)
{
    char *user = search_at_info(buf, 0);

    client_error_unknown_thread(user);
    free(user);
    return;
}
