/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** mem4
*/

#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include "libs/arr.h"
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

reply_t *create_reply(char *body, user_t *creator)
{
    reply_t *reply = alloc(sizeof(channel_t), reply_free);

    if (reply == NULL) {
        PERR_NORET("Couldn't Alloc Reply");
        return NULL;
    }
    reply->time = time(NULL);
    reply->uuid = generate_uuid();
    reply->body = strcreate(body);
    reply->creator = creator;
    return reply;
}

void dm_free(void *ptr)
{
    dm_t *dm = ptr;

    if (dm == NULL) {
        return;
    }
    destroy(dm->message);
    ptr_free(ptr);
}

dm_t *create_dm(
    server_t *server, user_t *sender, user_t *receiver, char *message)
{
    dm_t *dm = alloc(sizeof(dm_t), dm_free);

    if (dm == NULL) {
        PERR_NORET("Couldn't Alloc Dm");
        return NULL;
    }
    dm->time = time(NULL);
    dm->sender = sender;
    dm->receiver = receiver;
    dm->message = strcreate(message);
    arr_pushback(&(server->dms), dm);
    return dm;
}
