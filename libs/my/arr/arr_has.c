/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** arr_has
*/

#include <stdbool.h>

#include "libs/arr.h"

bool arr_has(void *_arr, void *elem)
{
    char **arr = _arr;

    while (*arr) {
        if (*arr == elem) {
            return true;
        }
        arr++;
    }
    return false;
}
