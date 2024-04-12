/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** strcreate
*/

#include <string.h>

#include "libs/mem.h"
#include "libs/str.h"

char *strcreate(const char *init)
{
    size_t len = strlen(init);
    char *str = ptr_alloc((len + 1) * sizeof(char));

    return strcpy(str, init);
}

char *strncreate(const char *init, size_t n)
{
    char *str = ptr_alloc((n + 1) * sizeof(char));

    strncpy(str, init, n);
    str[n] = '\0';
    return str;
}
