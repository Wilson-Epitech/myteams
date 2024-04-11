/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** get_size
*/

#include "libs/mem.h"

size_t ptrlen(void *_ptr, size_t elem_size)
{
    size_t size = 0;
    char *ptr = _ptr;

    while (*(ptr + (size * elem_size))) {
        size++;
    }
    return size;
}
