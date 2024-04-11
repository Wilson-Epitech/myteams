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
