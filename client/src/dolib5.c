/*
** MYTEAMS PROJECT, 2024
** dosend.c
** File description:
** dosend.c
*/

#include <stdlib.h>

#include "../libs/myteams/logging_client.h"
#include "cmd.h"
#include "libs/mem.h"

void do033(char *buf)
{
    SMART char *uuid = get_info(buf, 0);
    SMART char *mess = get_info(buf, 1);

    client_event_private_message_received(uuid, mess);
}

void do039(char *buf)
{
    SMART char *team_uuid = get_info(buf, 0);
    SMART char *team_name = get_info(buf, 1);
    SMART char *team_description = get_info(buf, 2);

    client_print_team_created(team_uuid, team_name, team_description);
}

void do040(char *buf)
{
    SMART char *channel_uuid = get_info(buf, 0);
    SMART char *channel_name = get_info(buf, 1);
    SMART char *channel_description = get_info(buf, 2);

    client_print_channel_created(
        channel_uuid, channel_name, channel_description);
}

void do041(char *buf)
{
    SMART char *thread_uuid = get_info(buf, 0);
    SMART char *user_uuid = get_info(buf, 1);
    SMART char *thread_timestamp = get_info(buf, 2);
    SMART char *thread_title = get_info(buf, 3);
    SMART char *thread_body = get_info(buf, 4);

    client_print_thread_created(thread_uuid, user_uuid, atol(thread_timestamp),
        thread_title, thread_body);
}

void do042(char *buf)
{
    SMART char *thread_uuid = get_info(buf, 0);
    SMART char *user_uuid = get_info(buf, 1);
    SMART char *reply_timestamp = get_info(buf, 2);
    SMART char *reply_body = get_info(buf, 3);

    client_print_reply_created(
        thread_uuid, user_uuid, atol(reply_timestamp), reply_body);
}
