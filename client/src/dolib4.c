/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** dolib2
*/

#include <stdbool.h>

#include "../libs/myteams/logging_client.h"
#include "cmd.h"
#include "libs/mem.h"

void do012(char *buf)
{
    SMART char *team_uuid = get_info(buf, 0);
    SMART char *thread_uuid = get_info(buf, 1);
    SMART char *user_uuid = get_info(buf, 2);
    SMART char *reply_body = get_info(buf, 3);

    client_event_thread_reply_received(
        team_uuid, thread_uuid, user_uuid, reply_body);
}
