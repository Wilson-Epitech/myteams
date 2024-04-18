/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** load_reply
*/

#include "database.h"
#include "libs/file.h"
#include "libs/mem.h"
#include "libs/str.h"
#include "server.h"

// static void alloc_reply()

reply_t **load_replies()
{
    SMART char *text = get_content(DATABASE_DIR "teams.txt");
    SMART char **token = split(text, '\n');

    // for (size_t i = 0; token[i]; i++) {
    //     printf("index=[%ld] str=[%s]\n", i, token[i]);
    // }

    return arr_alloc(1);
}
