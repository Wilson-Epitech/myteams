/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** split
*/

#include <string.h>

#include "libs/mem.h"
#include "libs/str.h"

char **split(char *str, char del)
{
    size_t count = strcount(str, del);
    char **arr = arr_alloc(sizeof(char *), count + 2);
    size_t index = 0;
    size_t len = 0;
    char *next = NULL;

    do {
        next = strchr(str, del);
        len = ((next == NULL) ? strlen(str) : (size_t)(next - str));
        arr[index] = ptr_alloc(sizeof(char) * (len + 1));
        strncpy(arr[index], str, len);
        arr[index][len] = '\0';
        index += 1;
        str += len + 1;
    } while (index <= count);
    return arr;
}
