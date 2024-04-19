/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** load_channels
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "database.h"
#include "libs/arr.h"
#include "libs/file.h"
#include "libs/mem.h"
#include "libs/str.h"
#include "server.h"

static bool is_thread(char *token)
{
    if (token == NULL) {
        return false;
    }
    if (token[0] != '\t') {
        return false;
    }
    return true;
}

static void add_thread(channel_t *channel, thread_t **threads, char *token)
{
    for (; strcmp(token, (*threads)->uuid) != 0; threads++) {
    }
    arr_pushback(&(channel->threads), *threads);
}

// uuid
// name
// description
// threads
//         thread uuid
//         thread uuid
channel_t **load_channels(void)
{
    SMART char *text = get_content(DATABASE_DIR "channels.txt");
    SMART char **tokens = split(text, '\n');
    SMART thread_t **threads = load_threads();
    channel_t *curr = NULL;
    channel_t **channels = arr_alloc(1);

    set_destructor(channels, ptr_free);
    for (size_t i = 0; tokens[i];) {
        curr = alloc(sizeof(channel_t), channel_free);
        curr->uuid = strcreate(tokens[i]);
        curr->name = strcreate(tokens[i + 1]);
        curr->description = strcreate(tokens[i + 2]);
        curr->threads = arr_alloc(1);
        for (i += 4; is_thread(tokens[i]); i++) {
            add_thread(curr, threads, tokens[i] + 1);
        }
        arr_pushback(&channels, curr);
    }
    return channels;
}
// printf("uuid=[%s] time=[%ld] title=[%s] msg=[%s] replies[%ld]\n",
//     curr->uuid, curr->time, curr->title, curr->message,
//     arrlen(curr->replies));
