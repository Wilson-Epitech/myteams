/*
** MYTEAMS PROJECT, 2024
** my-ftp
** File description:
** arr
*/

#pragma once

#include <stddef.h>

/*
    return the length of a NULL terminated array
*/
size_t arrlen(const void *arr);

/*
    print all elements of the array
*/
void arrdebug(char *const *arr);

/*
    add a new element to the array (&arr)
*/
void *arr_pushback(void *arr, void *elem);

/*
    remove an element at a certain index if found
*/
void arr_remove_idx(void *_arr, size_t index);

/*
    remove elem if found
*/
void arr_remove_ptr(void *_arr, void *elem);

/*
    shift the array to the left. (after a remove/pop)
*/
void arr_shift_left(char **arr);
