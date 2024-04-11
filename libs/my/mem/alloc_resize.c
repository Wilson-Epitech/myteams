/*
** MYTEAMS PROJECT, 2024
** my-ftp
** File description:
** alloc
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libs/mem.h"

void *alloc_resize(void *old, size_t n_elem_to_add, size_t elem_size)
{
    destructor_t destructor = get_destructor(old);
    size_t len = ptrlen(old, elem_size);
    size_t new_len = len + n_elem_to_add;
    void *new = malloc(sizeof(destructor) + ((new_len + 1) * elem_size));

    if (new == NULL) {
        return NULL;
    }
    new += sizeof(destructor);
    set_destructor(new, destructor);
    memcpy(new, old, elem_size * len);
    memset(new + (len * elem_size), 0, elem_size * (n_elem_to_add + 1));
    destroy_parent(old);
    return new;
}
