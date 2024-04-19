/*
** MYTEAMS PROJECT, 2024
** dosend.c
** File description:
** dosend.c
*/

#include <stdlib.h>

#include "../libs/myteams/logging_client.h"
#include "cmd.h"

void do033(char *buf)
{
    char *uuid = search_at_info(buf, 0);
    char *mess = search_at_info(buf, 1);

    client_event_private_message_received(uuid, mess);
    free(mess);
    free(uuid);
    return;
}

static int help28(char *buf, int i)
{
    int ret = 0;
    char *uuid = search_at_info(buf, (i * 3));
    char *name = search_at_info(buf, (i * 3));
    char *description = search_at_info(buf, (i * 3));

    if (uuid[0] == 0)
        ret = 1;
    else
        client_print_teams(uuid, name, description);
    free(uuid);
    free(name);
    free(description);
    return ret;
}

void do028(char *buf)
{
    for (int i = 0; help28(buf, i) != 1; i++)
        ;
    return;
}

static int help27(char *buf, int i)
{
    int ret = 0;
    char *uuid = search_at_info(buf, (i * 3));
    char *name = search_at_info(buf, (i * 3));
    char *description = search_at_info(buf, (i * 3));

    if (uuid[0] == 0)
        ret = 1;
    else
        client_team_print_channels(uuid, name, description);
    free(uuid);
    free(name);
    free(description);
    return ret;
}

void do027(char *buf)
{
    for (int i = 0; help27(buf, i) != 1; i++) {
    }
    return;
}
