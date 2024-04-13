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

char *stradd_s(char **str, char *add)
{
    size_t len_1 = strlen(*str);
    size_t len_2 = strlen(add);
    char *new = alloc_resize(*str, len_2, sizeof(char));

    strcpy(new + len_1, add);
    *str = new;
    return new;
}
