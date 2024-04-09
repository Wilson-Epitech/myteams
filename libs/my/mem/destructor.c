/*
** MYTEAMS PROJECT, 2024
** my-ftp
** File description:
** constructor
*/

#include <stdlib.h>

#include "libs/mem.h"

void ptr_free(void *ptr)
{
    free(ptr - sizeof(destructor_t));
}

void arr_free(void *ptr)
{
    void **arr = ptr;

    while (*arr) {
        destroy(*arr);
        arr += 1;
    }
    ptr_free(ptr);
}
