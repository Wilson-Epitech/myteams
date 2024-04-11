/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** stradd_chr
*/

#include <string.h>

#include "libs/mem.h"
#include "libs/str.h"

char *stradd_c(char **str, char c)
{
    size_t len = strlen(*str);
    char *new = alloc_resize(*str, 1, sizeof(char));

    new[len] = c;
    *str = new;
    return new;
}
