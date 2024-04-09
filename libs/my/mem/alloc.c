/*
** MYTEAMS PROJECT, 2024
** my-ftp
** File description:
** alloc
*/

#include <stdlib.h>

#include "libs/mem.h"

void *alloc(size_t size, destructor_t destructor)
{
    void *ptr = malloc(sizeof(destructor) + size);

    if (ptr == NULL) {
        return NULL;
    } else {
        ptr += sizeof(destructor);
        set_destructor(ptr, destructor);
    }
    return ptr;
}
