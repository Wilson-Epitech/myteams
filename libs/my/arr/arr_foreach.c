/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** arr_foreach
*/

#include <stdarg.h>

#include "libs/arr.h"

void arr_foreach(void *_arr, void (*function)(void *))
{
    char **arr = _arr;

    for (; *arr; arr++) {
        function(*arr);
    }
}

void arr_foreach_arg(void *_arr, void (*function)(void *, va_list), ...)
{
    char **arr = _arr;
    va_list ap;
    va_list cpy;

    va_start(ap, function);
    for (; *arr; arr++) {
        va_copy(cpy, ap);
        function(*arr, cpy);
        va_end(cpy);
    }
    va_end(ap);
}
