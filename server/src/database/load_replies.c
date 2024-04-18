/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** load_reply
*/

#include <stdio.h>
#include <stdlib.h>

#include "database.h"
#include "libs/arr.h"
#include "libs/file.h"
#include "libs/mem.h"
#include "libs/str.h"
#include "server.h"

reply_t **load_replies(void)
{
    SMART char *text = get_content(DATABASE_DIR "replies.txt");
    SMART char **tokens = split(text, '\n');
    reply_t **replies = arr_alloc(1);
    reply_t *curr;

    set_destructor(replies, ptr_free);
    for (size_t i = 0; tokens[i]; i += 3) {
        curr = alloc(sizeof(reply_t), reply_free);
        curr->uuid = strcreate(tokens[i]);
        curr->time = atol(tokens[i + 1]);
        curr->body = strcreate(tokens[i + 2]);
        arr_pushback(&replies, curr);
    }
    return replies;
}
