/*
** MYTEAMS PROJECT, 2024
** my-ftp
** File description:
** concat
*/

#include <stdio.h>
#include <stdlib.h>

#include "libs/str.h"

char *strconcat(char *left, char *right)
{
    size_t size = snprintf(NULL, 0, "%s%s", left, right);
    char *s = malloc(size + 1);

    sprintf(s, "%s%s", left, right);
    return s;
}
