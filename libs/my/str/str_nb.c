/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** str_int
*/

#include <stdio.h>

#include "libs/mem.h"
#include "libs/str.h"

char *str_int(int x)
{
    size_t size = snprintf(NULL, 0, "%d", x);
    char *s = ptr_alloc(size + 1);

    sprintf(s, "%d", x);
    return s;
}

char *str_long(long x)
{
    size_t size = snprintf(NULL, 0, "%ld", x);
    char *s = ptr_alloc(size + 1);

    sprintf(s, "%ld", x);
    return s;
}

char *str_uint(unsigned x)
{
    size_t size = snprintf(NULL, 0, "%u", x);
    char *s = ptr_alloc(size + 1);

    sprintf(s, "%u", x);
    return s;
}

char *str_ulong(unsigned long x)
{
    size_t size = snprintf(NULL, 0, "%lu", x);
    char *s = ptr_alloc(size + 1);

    sprintf(s, "%lu", x);
    return s;
}
