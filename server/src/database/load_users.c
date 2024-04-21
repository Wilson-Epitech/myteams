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

#include "../libs/myteams/logging_server.h"
#include "database.h"
#include "libs/arr.h"
#include "libs/file.h"
#include "libs/mem.h"
#include "libs/str.h"
#include "server.h"

user_t **load_users(void)
{
    SMART char *text = get_content(DATABASE_DIR "users.txt");
    SMART char **tokens = (text) ? split(text, '\n') : arr_alloc(1);
    user_t *curr = NULL;
    user_t **users = arr_alloc(1);

    for (size_t i = 0; tokens[i]; i += 2) {
        curr = alloc(sizeof(user_t), user_free);
        curr->uuid = strcreate(tokens[i]);
        curr->name = strcreate(tokens[i + 1]);
        curr->loged = false;
        server_event_user_loaded(curr->uuid, curr->name);
        arr_pushback(&users, curr);
    }
    return users;
}
