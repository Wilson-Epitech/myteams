/*
** MYTEAMS PROJECT, 2024
** myteams
** File description:
** save
*/
/*
** MYTEAMS PROJECT, 2024
** myteams
** File description:
** build
*/

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "libs/def.h"
#include "server.h"

int save_users(user_t **users)
{
    FILE *file = fopen(SAVE_DIRECTORY "users.txt", "w");

    if (!file) {
        PERR_NORET("Open failed");
        return FAILURE;
    }
    for (size_t i = 0; users[i] != NULL; i++) {
        fprintf(file, "%s\n%s\n", users[i]->uuid, users[i]->name);
    }
    fclose(file);
    return 0;
}
