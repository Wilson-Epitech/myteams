/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** add
*/

#include "libs/arr.h"
#include "libs/mem.h"

void *arr_pushback(void *arr, void *elem)
{
    size_t len = arrlen(*((char ***)arr));
    char **new = alloc_resize(*((char ***)arr), 1, sizeof(void *));

    new[len] = elem;
    *((char ***)arr) = new;
    return new;
}
