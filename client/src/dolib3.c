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

void do009(char *buf)
{
    SMART char *team_uuid = get_info(buf, 0);
    SMART char *team_name = get_info(buf, 1);
    SMART char *team_description = get_info(buf, 2);

    client_event_team_created(team_uuid, team_name, team_description);
}

void do010(char *buf)
{
    SMART char *channel_uuid = get_info(buf, 0);
    SMART char *channel_name = get_info(buf, 1);
    SMART char *channel_description = get_info(buf, 2);

    client_event_channel_created(
        channel_uuid, channel_name, channel_description);
}

void do011(char *buf)
{
    SMART char *thread_uuid = get_info(buf, 0);
    SMART char *user_uuid = get_info(buf, 1);
    SMART char *thread_timestamp = get_info(buf, 2);
    SMART char *thread_title = get_info(buf, 3);
    SMART char *thread_body = get_info(buf, 4);

    client_event_thread_created(thread_uuid, user_uuid, atol(thread_timestamp),
        thread_title, thread_body);
}

void do026(char *buf)
{
    size_t index = 0;
    char *th_uuid = NULL;
    char *us_uuid = NULL;
    char *time = NULL;
    char *title = NULL;
    char *body = NULL;

    do {
        va_destroy(5, th_uuid, us_uuid, time, title, body);
        th_uuid = get_info(buf, index);
        us_uuid = get_info(buf, index + 1);
        time = get_info(buf, index + 2);
        title = get_info(buf, index + 3);
        body = get_info(buf, index + 4);
        if (th_uuid && us_uuid && time && title && body) {
            client_channel_print_threads(
                th_uuid, us_uuid, atol(time), title, body);
        }
        index += 5;
    } while (th_uuid && us_uuid && time && title && body);
}

void do025(char *buf)
{
    size_t index = 0;
    char *th_uuid = NULL;
    char *us_uuid = NULL;
    char *time = NULL;
    char *body = NULL;

    do {
        destroy(th_uuid);
        destroy(us_uuid);
        destroy(time);
        destroy(body);
        th_uuid = get_info(buf, index);
        us_uuid = get_info(buf, index + 1);
        time = get_info(buf, index + 2);
        body = get_info(buf, index + 3);
        if (th_uuid && us_uuid && time && body) {
            client_thread_print_replies(th_uuid, us_uuid, atol(time), body);
        }
        index += 4;
    } while (th_uuid && us_uuid && time && body);
}
