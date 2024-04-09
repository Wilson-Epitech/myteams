/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** debug
*/

#include <stdio.h>

#include "libs/arr.h"

void arrdebug(char *const *arr)
{
    for (size_t i = 0; arr[i]; i++) {
        printf("index=[%ld] str=[%s]\n", i, arr[i]);
    }
}
