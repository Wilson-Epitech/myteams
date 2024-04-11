/*
** MYTEAMS PROJECT, 2024
** my-ftp
** File description:
** concat
*/

#include <stdio.h>

#include "libs/mem.h"
#include "libs/str.h"

char *strconcat(const char *left, const char *right)
{
    size_t size = snprintf(NULL, 0, "%s%s", left, right);
    char *s = ptr_alloc(size + 1);

    sprintf(s, "%s%s", left, right);
    return s;
}
