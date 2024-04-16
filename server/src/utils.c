/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** utils
*/

#include <stdio.h>
#include <string.h>

#include "libs/mem.h"
#include "libs/str.h"
#include "server.h"

char *generate_uuid(server_t *server)
{
    char *uuid = ptr_alloc(sizeof(char) * (36 + 1));

    sprintf(uuid, "%036ld", server->uuid);
    server->uuid += 1;
    return uuid;
}

void remove_quote(char **arr)
{
    char *tmp;

    while (*arr) {
        tmp = *arr;
        arr[0] = strncreate((*arr) + 1, strlen(*arr) - 2);
        destroy(tmp);
        arr++;
    }
}

team_t *find_team(team_t **teams, char *team_uuid)
{
    while (*teams) {
        if (strcmp((*teams)->uuid, team_uuid) == 0) {
            return *teams;
        }
        teams++;
    }
    return NULL;
}

channel_t *find_channel(channel_t **channels, char *channel_uuid)
{
    while (*channels) {
        if (strcmp((*channels)->uuid, channel_uuid) == 0) {
            return *channels;
        }
        channels++;
    }
    return NULL;
}

thread_t *find_thread(thread_t **threads, char *thread_uuid)
{
    while (*threads) {
        if (strcmp((*threads)->uuid, thread_uuid) == 0) {
            return *threads;
        }
        threads++;
    }
    return NULL;
}
