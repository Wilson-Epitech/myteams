/*
** MYTEAMS PROJECT, 2024
** teams
** File description:
** debug
*/

#include <stdio.h>
#include <string.h>

#include "libs/arr.h"

void arrdebug(char *const *arr)
{
    for (size_t i = 0; arr[i]; i++) {
        printf("index=[%ld] len=[%ld] str=[%s]\n", i, strlen(arr[i]), arr[i]);
    }
}
