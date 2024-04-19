/*
** MYTEAMS PROJECT, 2024
** myteams
** File description:
** load_db
*/

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "database.h"
#include "libs/def.h"
#include "libs/mem.h"
#include "libs/str.h"
#include "libs/arr.h"

static size_t get_file_size(char *file)
{
    struct stat st;
    size_t size = 0;

    if (stat(file, &st) == -1) {
        PERR_NORET("Stat failed");
        return size;
    }
    size = st.st_size;
    return size;
}

static char **get_content_from_file(char *filepath)
{
    char *buffer = NULL;
    char **array = arr_alloc(1);
    size_t size = get_file_size(filepath);
    FILE *file = fopen(filepath, "r");

    if (size == 0)
        return NULL;
    if (!file) {
        PERR_NORET("Open failed");
        return NULL;
    }
    buffer = malloc((sizeof(char)) * (size + 1));
    if (fread(buffer, sizeof(char), size, file) == 0) {
        PERR_NORET("Fread failed");
        return NULL;
    }
    fclose(file);
    buffer[size] = '\0';
    array = split(buffer, '\n');
    return array;
}

static void fill_users(user_t **users, user_t *user, char **array)
{
    size_t i = 0;

    while (array[i] != NULL) {
        if (strlen(array[i]) == 0) {
            i += 1;
            continue;
        }
        user = alloc(sizeof(user_t), user_free);
        user->uuid = strcreate(array[i]);
        if (strlen(array[i + 1]) == 0) {
            i += 1;
            continue;
        }
        user->name = strcreate(array[i + 1]);
        user->loged = 0;
        arr_pushback(&users, user);
        i += 2;
    }
}

user_t **load_users(void)
{
    user_t **users = arr_alloc(1);
    user_t *user = NULL;
    char **array = get_content_from_file(DATABASE_DIR "users.txt");

    if (array == NULL)
        return users;
    fill_users(users, user, array);
    return users;
}
