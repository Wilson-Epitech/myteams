/*
** MYTEAMS PROJECT, 2024
** my-ftp
** File description:
** arr
*/

#pragma once

#include <stdarg.h>
#include <stdbool.h>
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
void arr_remove_idx(void *_arr, size_t index, bool free_elem);

/*
    remove elem if found
*/
void arr_remove_ptr(void *_arr, void *elem, bool free_elem);

/*
    shift the array to the left. (after a remove/pop)
*/
void arr_shift_left(char **arr);

/*
    checks if an array contains an element
*/
bool arr_has(void *_arr, void *elem);

/**
 * applies a function to every element of an array.
 */
void arr_foreach(void *_arr, void (*function)(void *));

/**
 * applies a function to every element of an array.
 * give the va_list to the function.
 */
void arr_foreach_arg(void *_arr, void (*function)(void *, va_list), ...);
