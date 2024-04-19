/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** mem3
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

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

channel_t *create_channel(char *name, char *description, team_t *parent)
{
    channel_t *channel;

    for (size_t i = 0; parent->channels[i]; i++) {
        if (strcmp(parent->channels[i]->name, name) == 0) {
            return NULL;
        }
    }
    channel = alloc(sizeof(channel_t), channel_free);
    if (channel == NULL) {
        PERR_NORET("Couldn't Alloc Channel");
        return NULL;
    }
    channel->name = strcreate(name);
    channel->description = strcreate(description);
    channel->threads = arr_alloc(1);
    channel->uuid = generate_uuid();
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
    destroy(thread->replies);
    ptr_free(ptr);
}

thread_t *create_thread(char *title, char *message, channel_t *parent)
{
    thread_t *thread;

    for (size_t i = 0; parent->threads[i]; i++) {
        if (strcmp(parent->threads[i]->title, title) == 0) {
            return NULL;
        }
    }
    thread = alloc(sizeof(thread_t), thread_free);
    if (thread == NULL) {
        PERR_NORET("Couldn't Alloc Thread");
        return NULL;
    }
    thread->time = time(NULL);
    thread->uuid = generate_uuid();
    thread->title = strcreate(title);
    thread->message = strcreate(message);
    thread->replies = arr_alloc(1);
    return thread;
}
