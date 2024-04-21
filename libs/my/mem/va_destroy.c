/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** va_destroy
*/

#include <stdarg.h>
#include <stdio.h>

#include "libs/mem.h"

void va_destroy(size_t n, ...)
{
    va_list ap;

    va_start(ap, n);
    while (n) {
        destroy(va_arg(ap, void *));
        n--;
    }
    va_end(ap);
}
