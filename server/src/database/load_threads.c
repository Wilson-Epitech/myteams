/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** load_reply
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

static bool is_reply(char *token)
{
    if (token == NULL) {
        return false;
    }
    if (token[0] != '\t') {
        return false;
    }
    return true;
}

static void add_reply(thread_t *thread, reply_t **replies, char *token)
{
    for (; strcmp(token, (*replies)->uuid) != 0; replies++) {
    }
    arr_pushback(&(thread->replies), *replies);
}

thread_t **load_threads(void)
{
    SMART char *text = get_content(DATABASE_DIR "threads.txt");
    SMART char **tokens = split(text, '\n');
    SMART reply_t **replies = load_replies();
    thread_t *curr = NULL;
    thread_t **threads = arr_alloc(1);

    set_destructor(threads, ptr_free);
    for (size_t i = 0; tokens[i];) {
        curr = alloc(sizeof(thread_t), thread_free);
        curr->uuid = strcreate(tokens[i]);
        curr->time = atol(tokens[i + 1]);
        curr->title = strcreate(tokens[i + 2]);
        curr->message = strcreate(tokens[i + 3]);
        curr->replies = arr_alloc(1);
        for (i += 5; is_reply(tokens[i]); i++) {
            add_reply(curr, replies, tokens[i] + 1);
        }
        arr_pushback(&threads, curr);
    }
    return threads;
}
// printf("uuid=[%s] time=[%ld] title=[%s] msg=[%s] replies[%ld]\n",
//     curr->uuid, curr->time, curr->title, curr->message,
//     arrlen(curr->replies));
