/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** mem3
*/

#include <stdbool.h>
#include <stdio.h>

#include "libs/def.h"
#include "libs/mem.h"
#include "libs/str.h"
#include "server.h"

void channel_free(void *ptr)
{
    channel_t *channel = ptr;

    if (channel == NULL) {
        return;
    }
    destroy(channel->uuid);
    destroy(channel->name);
    destroy(channel->description);
    destroy(channel->threads);
    ptr_free(ptr);
}

channel_t *create_channel(server_t *server, char *name, char *description)
{
    channel_t *channel = alloc(sizeof(channel_t), channel_free);

    if (channel == NULL) {
        PERR_NORET("Couldn't Alloc Channel");
        return NULL;
    }
    channel->name = strcreate(name);
    channel->description = strcreate(description);
    channel->threads = arr_alloc(1);
    channel->uuid = generate_uuid(server);
    return channel;
}

void thread_free(void *ptr)
{
    thread_t *thread = ptr;

    if (thread == NULL) {
        return;
    }
    destroy(thread->uuid);
    destroy(thread->title);
    destroy(thread->message);
    destroy(thread->reply);
    ptr_free(ptr);
}

thread_t *create_thread(server_t *server, char *title, char *message)
{
    thread_t *thread = alloc(sizeof(thread_t), thread_free);

    if (thread == NULL) {
        PERR_NORET("Couldn't Alloc Thread");
        return NULL;
    }
    thread->uuid = generate_uuid(server);
    thread->title = strcreate(title);
    thread->message = strcreate(message);
    thread->reply = arr_alloc(1);
    return thread;
}
