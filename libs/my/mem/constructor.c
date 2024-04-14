/*
** MYTEAMS PROJECT, 2024
** my-ftp
** File description:
** constructor
*/

#include <stdio.h>

#include "libs/mem.h"

void *ptr_alloc(size_t size)
{
    return alloc(size, ptr_free);
}

void *arr_alloc(size_t len)
{
    void **arr = alloc(sizeof(void *) * len, arr_free);

    if (arr == NULL) {
        return NULL;
    }
    if (len) {
        arr[len - 1] = NULL;
    }
    return arr;
}
