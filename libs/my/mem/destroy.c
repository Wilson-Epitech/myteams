/*
** MYTEAMS PROJECT, 2024
** my-ftp
** File description:
** destroy
*/

#include <stdio.h>

#include "libs/mem.h"

void destroy(void *ptr)
{
    if (ptr == NULL) {
        return;
    }
    get_destructor(ptr)(ptr);
}

void destroy_parent(void *ptr)
{
    if (ptr == NULL) {
        return;
    }
    ptr_free(ptr);
}
