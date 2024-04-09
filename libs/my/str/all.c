/*
** MYTEAMS PROJECT, 2024
** my-ftp
** File description:
** forall
*/

#include "libs/str.h"

int strall(const char *str, int (*fn)(char c))
{
    while (*str) {
        if (fn(*str) == 0) {
            return 0;
        }
        str += 1;
    }
    return 1;
}
