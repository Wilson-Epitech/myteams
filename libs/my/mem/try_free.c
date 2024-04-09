/*
** MYTEAMS PROJECT, 2024
** my-ftp
** File description:
** try_free
*/

#include <stdlib.h>

#include "libs/mem.h"

void try_free(void *ptr)
{
    if (ptr != NULL) {
        free(ptr);
    }
}
