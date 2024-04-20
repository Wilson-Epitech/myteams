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
    return;
}
