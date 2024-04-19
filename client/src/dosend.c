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
