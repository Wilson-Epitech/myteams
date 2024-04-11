/*
** MYTEAMS PROJECT, 2024
** my-ftp
** File description:
** count
*/

#include "libs/str.h"

size_t strcount(const char *s, char c)
{
    size_t count = 0;

    while (*s) {
        if (*s == c) {
            count += 1;
        }
        s += 1;
    }
    return count;
}
