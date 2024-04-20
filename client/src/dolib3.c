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

// void do026(char *buf)
// {
//     size_t index = 0;
//     char *name = NULL;
//     char *uuid = NULL;
//     char *description = NULL;

//     do {
//         destroy(name);
//         destroy(uuid);
//         destroy(description);
//         name = search_at_info(buf, index);
//         uuid = search_at_info(buf, index + 1);
//         description = search_at_info(buf, index + 2);
//         if (name && uuid && description) {
//             client_channel_print_threads();
//             client_channel_print_threads(const char *thread_uuid, const char
//             *user_uuid, time_t thread_timestamp, const char *thread_title,
//             const char *thread_body);
//         }
//         index += 3;
//     } while (name && uuid && description);
// }
