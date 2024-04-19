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

// sender
// receiver
// time
// message
dm_t **load_dms(user_t **users)
{
    SMART char *text = get_content(DATABASE_DIR "dms.txt");
    SMART char **tokens = (text) ? split(text, '\n') : arr_alloc(1);
    dm_t *curr = NULL;
    dm_t **dms = arr_alloc(1);

    for (size_t i = 0; tokens[i]; i += 4) {
        curr = alloc(sizeof(dm_t), user_free);
        curr->sender = find_user_by_uuid(users, tokens[i]);
        curr->receiver = find_user_by_uuid(users, tokens[i + 1]);
        curr->time = atol(tokens[i + 2]);
        curr->message = strcreate(tokens[i + 3]);
        arr_pushback(&dms, curr);
    }
    return dms;
}
