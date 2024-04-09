/*
** MYTEAMS PROJECT, 2024
** my-ftp
** File description:
** len
*/

#include "libs/arr.h"

size_t arrlen(const void *arr)
{
    char **start = (char **)arr;
    char **end = (char **)arr;

    while (*end) {
        end += 1;
    }
    return (end - start);
}
