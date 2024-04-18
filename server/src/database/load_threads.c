/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** load_reply
*/

#include <stdio.h>
#include <stdlib.h>

#include "database.h"
#include "libs/file.h"
#include "libs/mem.h"
#include "libs/str.h"
#include "server.h"

static int add_replies(
    reply_t **replies, thread_t *curr, char **token, size_t i)
{
    for (; *replies; replies++) {
    }
}

thread_t **load_threads()
{
    SMART char *text = get_content(DATABASE_DIR "teams.txt");
    SMART char **token = split(text, '\n');
    reply_t **replies = load_replies();
    thread_t *curr = NULL;

    for (size_t i = 0; token[i]; i++) {
        curr = alloc(sizeof(thread_t), thread_free);
        curr->uuid = token[i];
        curr->time = atol(token[i + 1]);
        curr->title = token[i + 2];
        curr->message = token[i + 3];
        curr->replies = arr_alloc(1);
        i = add_replies(replies, curr, token, i + 5);
        // printf("index=[%ld] str=[%s]\n", i, token[i]);
    }

    return NULL;
}
