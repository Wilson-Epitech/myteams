/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** dolib2
*/

#include <stdbool.h>
#include <stdlib.h>

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

void do035(char *buf)
{
    SMART char *user_uuid = get_info(buf, 0);
    SMART char *message_body = get_info(buf, 1);

    client_event_private_message_received(user_uuid, message_body);
}

void do034(char *buf)
{
    size_t index = 0;
    char *sender_uuid = NULL;
    char *time = NULL;
    char *message = NULL;

    do {
        destroy(sender_uuid);
        destroy(time);
        destroy(message);
        sender_uuid = get_info(buf, index);
        time = get_info(buf, index + 1);
        message = get_info(buf, index + 2);
        if (sender_uuid && time && message) {
            client_private_message_print_messages(
                sender_uuid, atol(time), message);
        }
        index += 3;
    } while (sender_uuid && time && message);
}

void do008(char *buf)
{
    SMART char *uuid = get_info(buf, 0);
    SMART char *name = get_info(buf, 1);
    SMART char *status = get_info(buf, 2);

    client_print_user(uuid, name, atol(status));
}
