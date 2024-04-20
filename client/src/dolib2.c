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

void do036(char *buf)
{
    SMART char *old_uuid = search_at_info(buf, 0);
    SMART char *old_name = search_at_info(buf, 1);
    SMART char *new_uuid = search_at_info(buf, 2);
    SMART char *new_name = search_at_info(buf, 3);

    client_event_logged_out(old_uuid, old_name);
    client_event_logged_in(new_uuid, new_name);
}

void do028(char *buf)
{
    size_t index = 0;
    char *name = NULL;
    char *uuid = NULL;
    char *description = NULL;

    do {
        destroy(name);
        destroy(uuid);
        destroy(description);
        name = search_at_info(buf, index);
        uuid = search_at_info(buf, index + 1);
        description = search_at_info(buf, index + 2);
        if (name && uuid && description) {
            client_print_teams(uuid, name, description);
        }
        index += 3;
    } while (name && uuid && description);
}

void do027(char *buf)
{
    size_t index = 0;
    char *name = NULL;
    char *uuid = NULL;
    char *description = NULL;

    do {
        destroy(name);
        destroy(uuid);
        destroy(description);
        name = search_at_info(buf, index);
        uuid = search_at_info(buf, index + 1);
        description = search_at_info(buf, index + 2);
        if (name && uuid && description) {
            client_print_channel(uuid, name, description);
        }
        index += 3;
    } while (name && uuid && description);
}

void do023(char *buf)
{
    SMART char *user_uuid = search_at_info(buf, 0);
    SMART char *team_uuid = search_at_info(buf, 1);

    client_print_subscribed(user_uuid, team_uuid);
}

void do024(char *buf)
{
    SMART char *user_uuid = search_at_info(buf, 0);
    SMART char *team_uuid = search_at_info(buf, 1);

    client_print_unsubscribed(user_uuid, team_uuid);
}
