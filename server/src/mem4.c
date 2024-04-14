/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** mem4
*/

#include <stdbool.h>
#include <stdio.h>

#include "libs/def.h"
#include "libs/mem.h"
#include "libs/str.h"
#include "server.h"

void reply_free(void *ptr)
{
    reply_t *reply = ptr;

    if (reply == NULL) {
        return;
    }
    destroy(reply->uuid);
    destroy(reply->body);
    ptr_free(ptr);
}

void create_reply(server_t *server, char *body)
{
    reply_t *reply = alloc(sizeof(channel_t), reply_free);

    if (reply == NULL) {
        PERR_NORET("Couldn't Alloc Reply");
        return;
    }
    reply->uuid = generate_uuid(server);
    reply->body = strcreate(body);
}
