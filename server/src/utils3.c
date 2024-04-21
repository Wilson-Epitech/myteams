/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** utils3
*/

#include <stdio.h>
#include <string.h>

#include "server.h"

client_t *find_client(client_t **clients, user_t *user)
{
    for (size_t i = 0; clients[i]; i++) {
        if (clients[i]->user == user) {
            return clients[i];
        }
    }
    return NULL;
}

channel_t *find_channel_by_name(channel_t **channels, char *name)
{
    for (size_t i = 0; channels[i]; i++) {
        if (strcmp(channels[i]->name, name) == 0) {
            return channels[i];
        }
    }
    return NULL;
}

thread_t *find_thread_by_name(thread_t **threads, char *name)
{
    for (size_t i = 0; threads[i]; i++) {
        if (strcmp(threads[i]->title, name) == 0) {
            return threads[i];
        }
    }
    return NULL;
}
