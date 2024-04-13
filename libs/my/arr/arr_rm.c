/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** arr_pop
*/

#include "libs/arr.h"
#include "libs/mem.h"

void arr_remove_ptr(void *_arr, void *elem)
{
    char **arr = _arr;

    for (; *arr; arr++) {
        if (*arr == elem) {
            destroy(*arr);
            arr_shift_left(arr);
            return;
        }
    }
}

void arr_remove_idx(void *_arr, size_t index)
{
    char **arr = _arr;

    while (index && *arr) {
        index--;
        arr++;
    }
    if (*arr) {
        destroy(*arr);
        arr_shift_left(arr);
    }
}
